//----------------------------------------------------------------------
// Copyright(c) TQ Digital Entertainment, All Rights Reserved
// Author:  Xu Kaijie
// Created: 2010/3/3
// Describe:S3 Animation
//----------------------------------------------------------------------

#include <Common/S3AResourceBuilder.h>
#include <Common/Serialize/S3ASerializeListener.h>
#include <Common/S3AMathSerialize.h>
#include <Common/Serialize/S3ABinaryInputArchive.h>
#include "Common/S3AMeshData.h"


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
namespace S3AResourceBuilder
{


// 	S3ASkeleton* LoadSkeleton(S3ASerializeListener* pSL)
// 	{
// 		S3AStackMemoryMark memMarker(S3AGetDefaultStackAllocator());
// 
// 		S3ASkeleton* pSkel = NULL;
// 		S3AExpSkeletonHeader skelHeader;
// 		S3AExpSkeletonData skelData;
// 		pSL->Serialize(skelHeader,"Header");
// 		pSL->PushVersion(skelHeader.m_nVersion);
// 		pSL->Serialize(skelData,"Skeleton");
// 		pSL->PopVersion();
// 		pSkel = reinterpret_cast<S3ASkeleton*>(S3AExpDataConverter::CreateSkeleton(&skelData,skelHeader.m_nVersion));
// 		
// 
// 		S3AGlobalConfig* pCfg = reinterpret_cast<S3AGlobalConfig*>(S3AGetGlobalConfig());
// 		if (pCfg->m_bAutoSocketFromBoneEnable)
// 		{
// 			S3AArrayAlloc<const char*> arrSockePrefix(S3AGetDefaultStackAllocator());
// 			if (pCfg->m_arrSocketFromBoneNamePrefix.size() < 512)
// 			{
// 				for (xmUint nPCnt = 0; nPCnt < pCfg->m_arrSocketFromBoneNamePrefix.size(); ++nPCnt)
// 				{
// 					arrSockePrefix.push_back(pCfg->m_arrSocketFromBoneNamePrefix[nPCnt].c_str());
// 				}
// 				if (arrSockePrefix.size() > 0)
// 				{
// 					S3ASkelUtil::BuildSocketFromBone(pSkel,&arrSockePrefix[0],arrSockePrefix.size());
// 				}
// 
// 			}else{
// 				S3ALogError(S3A_ERR_INVALID_CALL,"Fail to auto build socket from bone : number of bone prefix is larger then 512\n");
// 			}
// 		}
// 
// //#pragma message( __FILE__ "(" STRING(__LINE__) ") : TODO Remove UpdateSkeletonGUID on loading")
// 		
// 
// 		return pSkel;
// 	}


// 	S3AAnimation* LoadAnimation(S3ASerializeListener* pSL)
// 	{
// 		S3AAnimation* pAnim = NULL;
// 		S3AExpAnimationHeader header;
// 		S3AExpAnimationData data;
// 		S3ABinaryInputArchive ar;
// 
// 		pSL->Serialize(header,"AnimationHeader");
// 
// 		if (header.m_nVersion == EXP_ANIM_VER_CURRENT)
// 		{
// 			pSL->PushVersion(header.m_nVersion);
// 			pSL->Serialize(data,"Animation");
// 			pSL->PopVersion();
// 			pAnim = reinterpret_cast<S3AAnimation*>(S3AExpDataConverter::CreateAnimation(&header,&data,NULL));
// 		}else{
// 			
// 			S3ALogError(S3A_ERR_INVALID_CALL,"Fail to load animation : LoadLegacyAnimation function to load legacy animation ");
// 		}
// 
// 		
// 
// 		return pAnim;
// 
// 	}

// 	S3AAnimation* LoadLegacyAnimation(S3ASerializeListener* pSL,IS3ASkeleton* pSkel)
// 	{
// 		S3AAnimation* pAnim = NULL;
// 		S3AExpAnimationHeader header;
// 		S3AExpAnimationData data;
// 		S3ABinaryInputArchive ar;
// 
// 		pSL->Serialize(header,"AnimationHeader");
// 
// 		bool bUpgradeOK = true;
// 		if (header.m_nIden != 'SANM')
// 		{
// 			S3ALogError(S3A_ERR_INVALID_CALL,"Invalid animation file");
// 			bUpgradeOK = false;
// 		}
// 
// 		if (bUpgradeOK)
// 		{
// 			pSL->PushVersion(header.m_nVersion);
// 			pSL->Serialize(data,"Animation");
// 			pSL->PopVersion();
// 
// 			bUpgradeOK = S3AExpDataConverter::UpgradeAnimationData(&header,&data
// 				,pSkel);
// 		}
// 
// 
// 
// 		if (bUpgradeOK)
// 		{
// 			pAnim = reinterpret_cast<S3AAnimation*>(S3AExpDataConverter::CreateAnimation(&header,&data,pSkel));
// 
// 		}else{
// 			S3ALogError(S3A_ERR_INVALID_CALL,"fail to upgrade animation\n");
// 		}
// 
// 		
// 
// 		return pAnim;
// 
// 	}

// 	bool LoadMeshFromFileVersion1(S3AExpMesh* pMesh,S3ASerializeListener* pSL)
// 	{
// 		pSL->Seek(0);
// 
// 		S3_ANIM_MODEL_FILE_HEADER modelHeader;
// 		char szModelName[128];
// 		S3_VERTEX_DATA* arrSrcVertexData = NULL;
// 		xmUint16* arrSrcIndexData = NULL;
// 		S3_LOD_MESHVIEW lodMeshView;
// 		S3_GEOMETRY_CHUNK* arrSubMeshInfo = NULL;
// 
// 		pSL->SerializeByte((xmUint8*)&modelHeader,sizeof(S3_ANIM_MODEL_FILE_HEADER));
// 		pSL->SerializeByte((xmUint8*)szModelName,modelHeader.nModelNameSize + 1);
// 		{
// 			arrSrcVertexData = new S3_VERTEX_DATA[modelHeader.nNumVertices];
// 			pSL->SerializeByte((xmUint8*)arrSrcVertexData,sizeof(S3_VERTEX_DATA)* modelHeader.nNumVertices);
// 		}
// 		pSL->SerializeByte((xmUint8*)&lodMeshView,sizeof(S3_LOD_MESHVIEW));
// 		pSL->SkipByte(sizeof(xmUint16)* modelHeader.nNumVertices);
// 		{
// 			arrSrcIndexData = new xmUint16[lodMeshView.nPrimitivesCount];
// 			pSL->SerializeByte((xmUint8*)arrSrcIndexData,sizeof(xmUint16)*lodMeshView.nPrimitivesCount);
// 		}
// 
// 		{
// 			arrSubMeshInfo = new S3_GEOMETRY_CHUNK[lodMeshView.nNumGeoChunks];
// 			pSL->SerializeByte((xmUint8*)arrSubMeshInfo,sizeof(S3_GEOMETRY_CHUNK)*lodMeshView.nNumGeoChunks);
// 		}
// 
// 
// 		{
// 			S3AExpMeshHeader& header = pMesh->m_header;
// 			header.m_nIdent = modelHeader.nIdent;
// 			header.m_nVersion = 0;
// 			header.m_strMaxFile = szModelName;//TODO Resolve String
// 			header.m_nSkelGUID.m_a = modelHeader.nGlobalSkeletonID;
// 			header.m_nSkelGUID.m_b = 0;
// 			header.m_nBoneNum = modelHeader.nBonesCount;
// 			header.m_nIndexNum = lodMeshView.nPrimitivesCount;
// 			header.m_nVertexNum = modelHeader.nNumVertices;
// 		}
// 
// 		{
// 			S3AExpMeshData& meshData = pMesh->m_mesh;
// 			//xmUint m_nIndexType;
// 			//xmUint m_nVertexType;
// 			//std::vector<xmUint8>	m_arrIndexBuffer;
// 			//std::vector<xmUint8>	m_arrVertexBuffer;
// 			//std::vector<std::string>	m_arrBoneName;
// 
// 			//std::vector<S3AExpMeshLOD>	m_arrMeshLOD;
// 			//std::vector<S3AExpBounding> m_arrBoneBound;
// 			//S3AExpBounding				m_meshBound;
// 
// 			meshData.m_nIndexType	= EXP_INDEX_TYPE_U16;
// 			meshData.m_nVertexType	= EXP_VT_SKIN_VERTEX_0;
// 			meshData.m_arrIndexBuffer.resize(sizeof(xmUint16)*	pMesh->m_header.m_nIndexNum);
// 			meshData.m_arrVertexBuffer.resize(sizeof(S3AExpVertexType0)* pMesh->m_header.m_nVertexNum);
// 			meshData.m_arrBoneName.clear();		//Not avaible
// 			meshData.m_arrMeshLOD.resize(1);
// 			meshData.m_arrBoneBound.clear();	//Not avaible
// 			meshData.m_meshBound.SetInvalid();	//Not avaible
// 
// 			//fill index buffer vertex buffer
// 			{
// 				memcpy(&meshData.m_arrIndexBuffer[0],arrSrcIndexData,meshData.m_arrIndexBuffer.size());
// 
// 				for (xmUint nVCnt = 0; nVCnt < modelHeader.nNumVertices; ++nVCnt)
// 				{
// 					S3AExpVertexType0* pDestV = (S3AExpVertexType0*)&meshData.m_arrVertexBuffer[nVCnt*sizeof(S3AExpVertexType0)];
// 					memcpy(pDestV,&arrSrcVertexData[nVCnt],sizeof(S3_VERTEX_DATA));
// 					pDestV->vc = 0xffffffff;
// 					pDestV->vi = 0;
// 				}
// 			}
// 
// 			//fill mesh
// 			{
// 				std::vector<S3AExpSubMesh>& arrSubMesh = pMesh->m_mesh.m_arrMeshLOD[0].m_arrSubMesh;
// 				arrSubMesh.resize(lodMeshView.nNumGeoChunks);
// 				for (xmUint nSubMeshCnt = 0; nSubMeshCnt < lodMeshView.nNumGeoChunks; ++nSubMeshCnt)
// 				{
// 					S3AExpSubMesh& subMesh = arrSubMesh[nSubMeshCnt];
// 
// 					subMesh.m_nIndexStart = arrSubMeshInfo[nSubMeshCnt].nPrimitiveIndexBegin;
// 					subMesh.m_nIndexCount = arrSubMeshInfo[nSubMeshCnt].nNumPrimitives;
// 					subMesh.m_nVertexStart = arrSubMeshInfo[nSubMeshCnt].nVertexIndexBegin;
// 					subMesh.m_nVertexCount = arrSubMeshInfo[nSubMeshCnt].nNumVertices;
// 					subMesh.m_subMeshBound.SetInvalid();
// 					subMesh.m_name = S3AStringConverter::ToString(arrSubMeshInfo[nSubMeshCnt].dwPartID);
// 					subMesh.m_submeshTag = subMesh.m_name;
// 					subMesh.m_arrBonePalette.clear();
// 				}
// 
// 			}
// 
// 		}
// 
// 		delete [] arrSrcVertexData;
// 		delete [] arrSrcIndexData;
// 		delete [] arrSubMeshInfo;
// 
// 		return true;
// 	}



// 	namespace UpdateInuseBoneAdapter
// 	{
// 		class BonePalatteAdapter : public S3AMeshUtil::UpdateInuseBoneHelper::BonePalatte
// 		{
// 		public:
// 
// 			std::vector<xmUint16> m_arrBone;
// 
// 			void Clear()
// 			{
// 				m_arrBone.clear();
// 			}
// 
// 			void PushBack(xmUint nBoneInd)
// 			{
// 				m_arrBone.push_back((xmUint16)nBoneInd);
// 			}
// 
// 
// 			xmUint GetPalatteSize() const
// 			{
// 				return (xmUint) m_arrBone.size();
// 			}
// 
// 
// 			xmUint GetBoneByIndex(xmUint nPalInd)
// 			{
// 				return m_arrBone[nPalInd];
// 			}
// 
// 
// 			void SetBoneByIndex(xmUint nPalInd,xmUint nBoneInd)
// 			{
// 				m_arrBone[nPalInd] = (xmUint16)nBoneInd;
// 			}
// 		};
// 
// 		class MeshAdapter : public S3AMeshUtil::UpdateInuseBoneHelper::Mesh
// 		{
// 		public:
// 
// 			S3ASkinVertexType0* m_pVertex;
// 			xmUint				m_nVNum;
// 
// 			xmUint			GetVertexNumber() const
// 			{
// 				return m_nVNum;
// 			}
// 
// 
// 
// 			xmUint	GetVertexInfluenceNumber(xmUint nVInd) const
// 			{
// 				return 4;
// 			}
// 
// 
// 			xmUint	GetVertexInfluenceBoneByIndex(xmUint nVInd,xmUint nInfInd) const
// 			{
// 				S3ASSERT(nVInd < m_nVNum);
// 				return ((xmUint8*)&m_pVertex[nVInd].m_nBoneIndice)[nInfInd];
// 			}
// 
// 
// 			float	GetVertexInfluenceWeightByIndex(xmUint nVInd,xmUint nInfInd) const
// 			{
// 				xmUint8 nWeight = ((xmUint8*)&m_pVertex[nVInd].m_nBoneWeight)[nInfInd];
// 				return (float)nWeight / 255.0f;
// 			}
// 
// 
// 			void	ResizeVertexInfluence(xmUint nVInd,xmUint nInfSize)
// 			{
// 				m_pVertex[nVInd].m_nBoneIndice = 0;
// 				m_pVertex[nVInd].m_nBoneWeight = 0;
// 			}
// 
// 
// 			void	SetVertexInfluenceBoneByIndex(xmUint nVInd,xmUint nInfInd,xmUint nBoneInd)
// 			{
// 				S3ASSERT_MSG(nInfInd < 4,"Fail to set bone influence : nInfInd out of range");
// 				S3ASSERT_MSG(nBoneInd <= 255, "Failt set bone influence : nBoneInd out of range");
// 				((xmUint8*)(&m_pVertex[nVInd].m_nBoneIndice))[nInfInd] = nBoneInd;
// 			}
// 
// 
// 			void	SetVertexInfluenceWeightByIndex(xmUint nVInd,xmUint nInfInd,float fWeight)
// 			{
// 				S3ASSERT_MSG(nInfInd < 4,"Fail to set bone influence : nInfInd out of range");
// 				S3ASSERT_MSG(fWeight <= 1.0f, "Failt set bone influence : nBoneInd out of range");
// 
// 				xmUint8 nWeight = (xmUint8)(fWeight * 255.0f);
// 				((xmUint8*)(&m_pVertex[nVInd].m_nBoneWeight))[nInfInd] = nWeight;
// 			}
// 		};
// 	}

// 	bool UpdateBonePalette(S3AMeshData* pMeshData)
// 	{
// 
// 		S3ASkinVertexType0* pVertexBuffer = pMeshData->GetVertexBuffer();
// 		S3ASSERT(NULL != pVertexBuffer);
// 
// 
// 		UpdateInuseBoneAdapter::MeshAdapter meshAdapter;
// 		UpdateInuseBoneAdapter::BonePalatteAdapter bonePalatteAdatper;
// 
// 		xmUint								nMaxBoneNum;
// 		std::vector<xmUint16> arrBonePalatte;
// 
// 
// 		meshAdapter.m_pVertex	= pVertexBuffer;
// 		meshAdapter.m_nVNum		= pMeshData->GetVertexNumber();
// 
// 		nMaxBoneNum = S3AMeshUtil::FindMaxBoneIndex(&meshAdapter) + 1;
// 		arrBonePalatte.resize(nMaxBoneNum);
// 
// 		const xmUint nSubMeshNum	= pMeshData->GetSubMeshNumber();
// 		for (xmUint nSubMeshCnt = 0; nSubMeshCnt < nSubMeshNum; ++nSubMeshCnt)
// 		{
// 			IS3ASubMeshData* pSubmesh = pMeshData->GetSubMesh(nSubMeshCnt);
// 
// 			if (pSubmesh->GetBonePaletteSize() == 0)
// 			{
// 
// 				meshAdapter.m_pVertex = pVertexBuffer + pSubmesh->GetVertexStart();
// 				meshAdapter.m_nVNum = pSubmesh->GetVertexCount();
// 
// 
// 
// 				S3AMeshUtil::UpdateInuseBone(&bonePalatteAdatper,&meshAdapter);
// 
// 				if (bonePalatteAdatper.m_arrBone.size() > 0)
// 				{
// 					pSubmesh->ResetBonePalatte(bonePalatteAdatper.m_arrBone.size(),&bonePalatteAdatper.m_arrBone[0]);
// 				}
// 
// 			}
// 		}
// 
// 		return true;
// 	}

	void UpdateBounding(S3AExpMeshData* pMesh)
	{
		S3ASSERT( EXP_VT_SKIN_VERTEX_0 == pMesh->m_nVertexType);
		const S3AExpVertexType0* arrVertex = reinterpret_cast<const S3AExpVertexType0*>(& pMesh->m_arrVertexBuffer[0]);
		std::vector<S3AExpSubMesh>& arrSubmesh = pMesh->m_arrMeshLOD[0].m_arrSubMesh;

		S3AExpAABBShape meshAABB;
		meshAABB.Init();

		for (xmUint nSubMeshCnt = 0; nSubMeshCnt < arrSubmesh.size(); ++nSubMeshCnt)
		{
			S3AExpSubMesh& submesh = arrSubmesh[nSubMeshCnt];

			S3AExpAABBShape subMeshAABB;
			subMeshAABB.Init();

			for (xmUint nVerCnt = 0; nVerCnt < submesh.m_nVertexCount; ++nVerCnt)
			{
				const S3AExpVertexType0& vertex = *(arrVertex + submesh.m_nVertexStart+nVerCnt);
				subMeshAABB.AddPoint(vertex.p);
			}

			meshAABB.Merge(subMeshAABB.m_vMin,subMeshAABB.m_vMax);

			submesh.m_subMeshBound.SetAABB(subMeshAABB.m_vMin,subMeshAABB.m_vMax);
		}

		pMesh->m_meshBound.SetAABB(meshAABB.m_vMin,meshAABB.m_vMax);
	}



	bool CreateMeshData(S3AMeshData* pMesh,const S3AExpMesh* pMeshExp)
	{

		const std::vector<S3AExpSubMesh>& arrSrcSubMesh = pMeshExp->m_mesh.m_arrMeshLOD[0].m_arrSubMesh;
		const xmUint nSubMeshNum = (xmUint)arrSrcSubMesh.size();

		pMesh->SetSource(pMeshExp->m_header.m_strMaxFile.c_str());
		pMesh->SetGlobalSkeletonID(pMeshExp->m_header.m_nSkelGUID);
		pMesh->ResetBuffer(pMeshExp->m_mesh.m_nIndexType,pMeshExp->m_header.m_nIndexNum
			,pMeshExp->m_header.m_nVertexNum
			,nSubMeshNum
			,pMeshExp->m_header.m_nBoneNum
			);

		//------------------------------------------------------------------------------
		//fill stream source
		//------------------------------------------------------------------------------
		const std::vector<xmUint8>& arrSrcIndexBuffer = pMeshExp->m_mesh.m_arrIndexBuffer;
		const std::vector<xmUint8>& arrSrcVertexBuffer = pMeshExp->m_mesh.m_arrVertexBuffer;
		memcpy(pMesh->GetIndexBuffer(),arrSrcIndexBuffer.size() > 0 ? &arrSrcIndexBuffer[0] : NULL,arrSrcIndexBuffer.size());
		memcpy(pMesh->GetVertexBuffer(),arrSrcVertexBuffer.size() > 0 ? &arrSrcVertexBuffer[0] : NULL,arrSrcVertexBuffer.size());

		//------------------------------------------------------------------------------
		//fill sub mesh
		//------------------------------------------------------------------------------
		for (xmUint nSubMeshCnt = 0; nSubMeshCnt < nSubMeshNum; ++nSubMeshCnt)
		{
			const S3AExpSubMesh& srcSubMesh = arrSrcSubMesh[nSubMeshCnt];
			IS3ASubMeshData* pSubMesh = pMesh->GetSubMesh(nSubMeshCnt);
			pSubMesh->Reset(srcSubMesh.m_nIndexStart,srcSubMesh.m_nIndexCount
				,srcSubMesh.m_nVertexStart,srcSubMesh.m_nVertexCount
				,0 //Unknown material id
				,&srcSubMesh.m_subMeshBound
				,srcSubMesh.m_arrBonePalette.size() > 0 ? &srcSubMesh.m_arrBonePalette[0] : NULL
				,srcSubMesh.m_arrBonePalette.size()
				,srcSubMesh.m_name.c_str()
				,srcSubMesh.m_submeshTag.c_str());
		}

		//------------------------------------------------------------------------------
		//fill skin info
		//------------------------------------------------------------------------------
		for (xmUint nBoneCnt = 0; nBoneCnt < pMeshExp->m_mesh.m_arrBoneName.size(); ++ nBoneCnt)
		{
			pMesh->SetBoneName(nBoneCnt,pMeshExp->m_mesh.m_arrBoneName[nBoneCnt].c_str());
			if (pMeshExp->m_mesh.m_arrBoneBound.size() > 0)
			{
				const S3AExpBounding&  bound = pMeshExp->m_mesh.m_arrBoneBound[nBoneCnt];
				S3ASSERT(bound.m_nShapeType == EXP_BS_BOX);
				pMesh->SetBoneBoundOBB(nBoneCnt,&bound.m_vPos,&bound.m_qRot,bound.m_boxShape.m_fXSize
					,bound.m_boxShape.m_fYSize
					,bound.m_boxShape.m_fZSize);
			}

		}


		//------------------------------------------------------------------------------
		//fill bounding
		//------------------------------------------------------------------------------
		xmVector3 vMin;
		xmVector3 vMax;
		pMeshExp->m_mesh.m_meshBound.GetAABB(vMin,vMax);
		pMesh->SetBoundingAABB(&vMin,&vMax);

		return true;

	}

	bool LoadMesh(S3AMeshData* pMesh,S3ASerializeListener* pSL)
	{
		//S3_TRY
		//{
			xmUint nMeshBegin = pSL->Tell();

			xmUint32		nIdent;	 // File Identity = 'S3MD'
			xmUint32		nVersion;	 // ��ʽ�汾��;
			bool bFileIdenOK = pSL->SerializeByte((xmUint8*)&nIdent,sizeof(xmUint32));

			if (!bFileIdenOK || nIdent != 'S3MD')
			{
				return false;
			}

			pSL->SerializeByte((xmUint8*)&nVersion,sizeof(xmUint32));
			pSL->Seek(nMeshBegin);



			bool bLoadOK = true;



			//if (nVersion >= EXP_MESH_VER_EMBED_MESH_DATA)
			//{
				pMesh->Serialize(pSL,"Mesh");

			//}
			//else{
// 
// 				S3AExpMesh meshExp;
// 
// 				if (nVersion >= EXP_MESH_VER_USE_SERIALZIE)
// 				{
// 					S3ASerialize(*pSL,meshExp,"Mesh");
// 				}else{
// 					bLoadOK = LoadMeshFromFileVersion1(&meshExp,pSL);
// 					UpdateBounding(&meshExp.m_mesh);
// 
// 					if (!bLoadOK)
// 					{
// 						S3ALogError(S3A_ERR_INVALID_CALL,"Fail to load mesh from version1 file");
// 					}
// 				}
// 
// 				if (bLoadOK)
// 				{
// 					bLoadOK = CreateMeshData(pMesh,&meshExp);
// 				}					
			//}


			//if (bLoadOK)
			//{
			//	bLoadOK = UpdateBonePalette(pMesh);
			//}

			return true;

		//}
		//S3_CATCH(...)
		//{
		//	S3ALogError(S3A_ERR_INVALID_CALL,"Fail to serialize mesh");
		//}

		return false;

	}


	bool	SaveMesh(S3AMeshData* pMesh, S3ASerializeListener* pSL)
	{
		//S3_TRY
		//{

			pMesh->Serialize(pSL, "Mesh");

			return true;

		//}
		//S3_CATCH(...)
		//{
		//	S3ALogError(S3A_ERR_INVALID_CALL,"Fail to serialize mesh");
		///}

		return false;

	}

	IS3AMeshData* LoadMeshFromBinaryFile(const char* filename)
	{
		S3AMeshData* pMeshData = NULL;
		S3ABinaryInputArchive ar;
		bool bLoadOK = ar.Open(filename);
		if (bLoadOK)
		{
			pMeshData = new S3AMeshData;
			bLoadOK = S3AResourceBuilder::LoadMesh(pMeshData,&ar);
			pMeshData->RemoveDegenerateTriangleInplace();
			if (!bLoadOK)
			{
				xmSafeDelete(pMeshData);
			}
		}

		if (!bLoadOK)
		{
			S3ALogError(S3A_ERR_INVALID_CALL,"Fail to load mesh from file %s:",filename);
		}

		return pMeshData;
	}

}