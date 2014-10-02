#include "Samples/Serialize/SampleFbxImport.h"
#include "Plugin/FbxImport/Module.h"
#include "SampleBrowser.h"

namespace ma
{
	//ADD_SAMPLE(FbxImport,SampleFbxImport);
	//Sample* CreateSample() { return new SampleFbxImport(); } 
	//GetSampleBrowser()->RegisterSample("FbxImport",CreateSample);

	SampleFbxImport::SampleFbxImport()
	{
		m_pAnimComponent = NULL;
	}

	void SampleFbxImport::LoadSkelMesh()
	{
		if (1)
		{
			
			LoadSkeletonMeshData("Fbx/TestBull.fbx");

			// Material
			{
				SamplerState diff;
				diff.SetTexturePath("FBX/TestBull_DM.png");

				MaterialParameter texureParam("u_texture");
				texureParam.SetValue(Any(diff));

				MaterialParameter colorParam("u_cDiffuseColor");
				colorParam.SetValue(Any(Vector4(1,1,1,1)));

				SubMaterialData subMatData;
				subMatData.m_strShaderName = "default";
				subMatData.m_strShaderMacro = "DIFFUSE;DIFFUSECOLOR;SKIN";
				subMatData.m_renderState.m_eCullMode = CULL_FACE_SIDE_FRONT;
				subMatData.m_arrParameters.push_back(texureParam);
				subMatData.m_arrParameters.push_back(colorParam);

				MaterialData matData;
				matData.AddSubMatData(subMatData);

				matData.SaveToFile("Fbx/TestBull.mat");
			}

			// AnimationSet
			{
				AnimationSetData animSetData;

				animSetData.AddAnimClip("Fbx/TestBull.ska","TestAnim");

				animSetData.SaveToFile("Fbx/TestBull.aniset");
			}
		}


		SceneNodePtr pTestBull = m_pScene->CreateNode("testBull");

		MeshComponentPtr pMeshComp = pTestBull->CreateComponent<MeshComponent>();
		pMeshComp->Load("FBX/TestBull.skn","FBX/TestBull.mat");
			
		AnimationComponentPtr pAnimationObject = pTestBull->CreateComponent<AnimationComponent>();
		pAnimationObject->Load("FBX/TestBull.aniset","FBX/TestBull.ske");
		pAnimationObject->PlayAnimation("TestAnim");

		m_pAnimComponent = pAnimationObject.get();

		pTestBull->Scale(1.0f / 50.0f);
	}

	void CreateMaterialData(const char* pszTexture,const char* pMatPath)
	{
		SamplerState diff;
		diff.SetTexturePath(pszTexture);

		MaterialParameter texureParam("u_texture");
		texureParam.SetValue(Any(diff));

		SubMaterialData subMatData;
		subMatData.m_strShaderName = "default";
		subMatData.m_strShaderMacro = "DIFFUSE";
		subMatData.m_renderState.m_eCullMode = CULL_FACE_SIDE_FRONT;
		subMatData.m_arrParameters.push_back(texureParam);

		MaterialData matData;
		matData.AddSubMatData(subMatData);

		matData.SaveToFile(pMatPath);
	}

	void SampleFbxImport::LoadSaticMesh()
	{
		if (1)
		{
			LoadStaticMeshData("FBX/shpere.FBX");
				
			LoadStaticMeshData("FBX/Box.FBX");

			LoadStaticMeshData("FBX/MovingPlatform.fbx");

			CreateMaterialData("FBX/Box.tga","FBX/Box.mat");
			
			CreateMaterialData("FBX/PlatformTexture.tga","FBX/MovingPlatform.mat");
		}

		
		SceneNodePtr pPlatform = m_pScene->CreateNode("Platform");
		MeshComponentPtr pMesh = pPlatform->CreateComponent<MeshComponent>();
		pMesh->Load("Fbx/MovingPlatform.skn","Fbx/MovingPlatform.mat");

		SceneNodePtr pBox = m_pScene->CreateNode("Box");
		MeshComponentPtr pBoxMesh = pBox->CreateComponent<MeshComponent>();
		pBoxMesh->Load("Fbx/Box.skn","Fbx/Box.mat");

	}

	void SampleFbxImport::Render()
	{
		if (m_pAnimComponent)
			m_pAnimComponent->DebugRender();

		Transform tsf;
		GetLineRender()->DrawTransform(tsf);
	}

	void SampleFbxImport::Load()
	{
		//Vector3 vEyePos = Vector3(0, 600, 800);
		Vector3 vEyePos = Vector3(10, -10, 10);
		Vector3 VAtPos = Vector3(0,0,0); 
		GetCamera()->GetSceneNode()->LookAt(vEyePos,VAtPos);

		FBXImporterModuleInit();

		LoadSaticMesh();

		LoadSkelMesh();
		
	}

	void SampleFbxImport::UnLoad()
	{
		FBXImporterModuleShutdown();
	}

}


