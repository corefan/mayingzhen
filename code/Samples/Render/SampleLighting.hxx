#include "SampleLighting.h"
#include "Plugin/FbxImport/Module.h"

namespace ma
{
	SampleLighting::SampleLighting()
	{
		m_pLigt = NULL;
	}

	void SampleLighting::Init(ApplicationBase* pApplication)
	{
		m_fMoveCameraSpeed = 0.80f;
		//m_pCamera->SetPositionWS( Vector3(0, 2, -3) );
		//Vector3 vEyePos(-2, 3, -5);
		//m_pCamera->LookAt(&vEyePos);
	}

	void SampleLighting::UnLoad()
	{
	}

	void SampleLighting::Load()
	{
		ASSERT(m_pScene);
		if (m_pScene == NULL)
			return;

		FBXImporter fbxImpor;
		fbxImpor.Initialize();

		MeshData* pMeshDataPlat = new MeshData;
		fbxImpor.LoadStaticMeshData("../Data/Fbx/MovingPlatform.fbx",pMeshDataPlat);
		SaveMeshToBinaryFile("../Data/Fbx/MovingPlatform.skn",pMeshDataPlat);
		SAFE_DELETE(pMeshDataPlat);

		MeshData* pMeshDataBox = new MeshData;
		fbxImpor.LoadStaticMeshData("../Data/Fbx/Box.fbx",pMeshDataBox);
		SaveMeshToBinaryFile("../Data/Fbx/Box.skn",pMeshDataBox);
		SAFE_DELETE(pMeshDataBox);

		SceneNode* pRootNode = m_pScene->GetRootNode(); 

		{
			GameObject* pGameObj = new GameObject(m_pScene,"Box");
			pRootNode->AddChildNode(pGameObj);

			MeshComponent* pMeshComp = new MeshComponent();
			pMeshComp->Load("../Data/Fbx/Box.skn","../Data/Fbx/Box.tga");
			pGameObj->AddComponent(pMeshComp);

			Vector3 vMin;
			Vector3 vMax;
			pMeshComp->GetBoundingAABB(vMin,vMax);
			AABB aabb;
			aabb.m_vMin = vMin;
			aabb.m_vMax = vMax;
			m_pCamera->FitAABB(aabb,0.5);
		}

// 		{
// 			GameObject* pGameObj = new GameObject(m_pScene,"Platform");
// 			pRootNode->AddChildNode(pGameObj);
// 
// 			MeshComponent* pMeshComp = new MeshComponent();
// 			pMeshComp->Load("../Data/Fbx/MovingPlatform.skn","../Data/Fbx/PlatformTexture.tga");
// 			pGameObj->AddComponent(pMeshComp);
// 			//pGameObj->TranslateWS(Vector3(0,0,0));
// 		}

		//light
		{
			m_pLigt = new Light(m_pScene,"Light");
			m_pLigt->SetLigtType(LIGHT_POINT);
			m_pLigt->SetRadius(3.0f);
			pRootNode->AddChildNode(m_pLigt);
			//m_pLigt->SetPositionWS(Vector3(2, 1, 0));
			
			GetRenderDevice()->AddLight(m_pLigt);
		}
		
		//m_pCamera->FitAABB(m_pScene->GetRootNode()->Get);

		m_pScene->Start();
	}

	void SampleLighting::Unload()
	{
		SAFE_DELETE(m_pLigt);	
	}

	void SampleLighting::Tick(float timeElapsed)
	{
		__super::Tick(timeElapsed);

		Input* pInput = GetInput();
		if (pInput == NULL)
			return;

		float fMoveSpeed = 5;
		float fMoveDis = fMoveSpeed * timeElapsed;

		Vector3 vLightPos = m_pLigt->GetPositionWS();
		if ( pInput->IsKeyDown(OIS::KC_W) )
		{
			vLightPos.y += fMoveDis;
		}
		if ( pInput->IsKeyDown(OIS::KC_S) )
		{
			vLightPos.y -= fMoveDis;
		}
		if ( pInput->IsKeyDown(OIS::KC_A) )
		{
			vLightPos.x -= fMoveDis;
		}
		if ( pInput->IsKeyDown(OIS::KC_D) )
		{
			vLightPos.x += fMoveDis;
		}
		m_pLigt->SetPositionWS(vLightPos);

	}

	void SampleLighting::Render()
	{
		__super::Render();

		Matrix4x4 matWS = m_pLigt->GetWorldMatrix();
		GetRenderDevice()->DrawWireSphere(matWS,m_pLigt->GetRadius(),COLOR_RGBA(255,0,0,255));
	}

}


