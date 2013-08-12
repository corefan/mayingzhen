#include "AnimationPlay.h"
#include "AnimationSet.h"
#include "Action.h"
#include "AnimationUtil.h"

namespace ma
{
	AnimationPlay::AnimationPlay(const char* pszSkePath)
	{
		m_pSkelAnim = NULL;
		m_pAnimSet = NULL;
		m_pSkeleton = NULL;
		m_pose = NULL;

		for (UINT i = 0; i < 256; ++i)
		{
			MatrixIdentity(&m_arrSkinMatrix[i]);
		}

		CreateSkeleton(pszSkePath);
	}

	AnimationPlay::~AnimationPlay()
	{
	}

	void AnimationPlay::Start()
	{
		ASSERT(m_pGameObj);
		if (m_pGameObj == NULL)
			return;

		m_arrRenderMesh.clear();
		UINT nMeshComp = m_pGameObj->GetTypeComponentNumber<MeshComponent>();
		for (UINT i = 0; i < nMeshComp; ++i)
		{
			MeshComponent* pMecomp = m_pGameObj->GetTypeComponentByIndex<MeshComponent>(i);
			ASSERT(pMecomp && pMecomp->GetRendMesh());
			if (pMecomp == NULL || pMecomp->GetRendMesh() == NULL)
				continue;

			m_arrRenderMesh.push_back(pMecomp->GetRendMesh());
		}
	}

	void AnimationPlay::Stop()
	{
		m_arrRenderMesh.clear();
	}

	void AnimationPlay::CreateSkeleton(const char* pSkePath)
	{
		ASSERT(pSkePath);
		if (pSkePath == NULL)
			return ;

		m_pSkeleton =  DeclareResource<Skeleton>(pSkePath);
		m_pSkeleton->LoadSync();

		const SkeletonPose* pRefPose = m_pSkeleton ? m_pSkeleton->GetResPose() : NULL;
		m_pose = pRefPose ? pRefPose->Clone() : NULL;

		m_pAnimSet = new AnimationSet(this);
	}

	void AnimationPlay::PlayAnimation(Action* pSkelAnim)
	{
		m_pSkelAnim = pSkelAnim;
	}

	void AnimationPlay::PlayAnimation(ActionID actionID)
	{
		if (m_pAnimSet == NULL)
			return;

		if (actionID < 0 || actionID >= m_pAnimSet->GetActionNumber())
			return;

		m_pSkelAnim = (Action*)m_pAnimSet->GetActionByIndex(actionID);
	}


	void AnimationPlay::PlayAnimation(const char* pszAnimName)
	{
		if (m_pAnimSet == NULL)
			return;

		m_pSkelAnim = (Action*)m_pAnimSet->GetActionByName(pszAnimName);
	}

	void AnimationPlay::AdvanceTime(float fTimeElepse)
	{
		if (m_pSkelAnim)
		{
			m_pSkelAnim->AdvanceTime(fTimeElepse);
		}
	}

	void AnimationPlay::EvaluateAnimation(float fWeight)
	{
		if (m_pSkeleton == NULL)
			return;

		const SkeletonPose* pRefPose = m_pSkeleton->GetResPose();
		if (pRefPose == NULL)
			return;

		AnimEvalContext evalContext;
		NodeTransform tsfIdent;
		//TransformSetIdentity(&tsfIdent);
		memset(&tsfIdent,0,sizeof(NodeTransform));
		evalContext.m_arrTSFLS.resize(pRefPose->GetNodeNumber(),tsfIdent);
		evalContext.m_pNodePos = m_pose;
		evalContext.m_refNodePos = pRefPose;

		if (m_pSkelAnim)
		{
			m_pSkelAnim->EvaluateAnimation(&evalContext,fWeight);
		}

		UINT nBoneNum = m_pSkeleton->GetBoneNumer();
		for (UINT i = 0; i < nBoneNum; ++i)
		{
			if (m_pose)
			{
				MatrixFromTransform(&m_arrSkinMatrix[i],& m_pose->GetTransformOS(i));
				MatrixMultiply(&m_arrSkinMatrix[i],& m_pSkeleton->GetBoneMatrixOSInv(i),&m_arrSkinMatrix[i]);
			}
			else
			{
				MatrixIdentity(&m_arrSkinMatrix[i]);
			}
		}

		for (UINT i = 0; i < m_arrRenderMesh.size(); ++i)
		{
			m_arrRenderMesh[i]->SetSkinMatrix(m_arrSkinMatrix,nBoneNum);
		}
	}

	void AnimationPlay::SetFrame(float fFrame)
	{
		if (m_pSkelAnim)
		{
			m_pSkelAnim->SetFrame(fFrame);
		}
	}

	void AnimationPlay::AddSkinMesh(RenderMesh* pRenderMesh)
	{
		m_arrRenderMesh.push_back(pRenderMesh);
	}
}
