#include "DeferredLightPass.h"
#include "../RenderSystem/RenderProfile.h"

namespace ma
{	
	DeferredLightPass::DeferredLightPass(Scene* pScene)
		:RenderPass(pScene)
	{

	}

	void DeferredLightPass::Init()
	{
		m_pAmbientLight = CreateTechnique("AmbientLight","DeferredLight","DeferredLight","AMBIENT_LIGHT");
		m_pAmbientLight->SetDepthWrite(false);

		m_pDirLight = CreateTechnique("DirectLight","DeferredLight","DeferredLight","DIRECT_LIGHT");
		m_pDirLight->SetDepthWrite(false);
		m_pDirLight->SetBlendMode(BM_ADD);

		m_pPointLight = CreateTechnique("PointLight","DeferredLight","DeferredLight","POINT_LIGHT");
		m_pPointLight->SetDepthWrite(false);
		m_pPointLight->SetBlendMode(BM_ADD);
	}

	void DeferredLightPass::Reset()
	{

	}

	void DeferredLightPass::Render()
	{
		RENDER_PROFILE(DefferedLighting);

		GetRenderSystem()->ClearBuffer(true,false,false,ColourValue::Black, 1.0f, 0);

		// AmbientLight
		Vector3 cAmbientColor = m_pScene->GetAmbientColor();
		m_pAmbientLight->SetParameter("light_color",Any(cAmbientColor));
		ScreenQuad::Render(m_pAmbientLight.get());	

		Matrix4 matView = GetRenderContext()->GetViewMatrix();

		UINT nLigtNumber = m_pScene->GetVisibleLightNum();
		for (UINT i = 0; i < nLigtNumber; ++i)
		{
			Light* pLight = m_pScene->GetVisibleLightByIndex(i);
			if (pLight == NULL)
				continue;

			GetRenderContext()->SetCurLight(pLight);

			if (pLight->GetLightType() == LIGHT_DIRECTIONAL)
			{       
				DirectonalLight* pDirLight = (DirectonalLight*)pLight;
				
				Uniform* pUniformDirES = m_pDirLight->GetShaderProgram()->GetUniform("light_dir_es");
				Uniform* pUniformColor = m_pDirLight->GetShaderProgram()->GetUniform("light_color");
					
				Quaternion qRotate = matView.extractQuaternion();
				Vector3 vDirES = qRotate * pDirLight->GetSceneNode()->GetForward();
				
				GetRenderSystem()->SetValue(pUniformDirES,vDirES);
				GetRenderSystem()->SetValue(pUniformColor,pLight->GetLightColor());

				ScreenQuad::Render(m_pDirLight.get());		
			}
			else if (pLight->GetLightType() == LIGHT_POINT)
			{
				PointLight* pPointLight = (PointLight*)pLight;
	
				Uniform* pUniformColor = m_pDirLight->GetShaderProgram()->GetUniform("light_color");
				Uniform* pUniformPosESRadius = m_pDirLight->GetShaderProgram()->GetUniform("light_pos_es_radius");
				
				Vector3 vPosES = matView * pPointLight->GetSceneNode()->GetPos();
				Vector4 vPosESRadius(vPosES.x,vPosES.y,vPosES.z,pPointLight->GetRadius());
				
				GetRenderSystem()->SetValue(pUniformColor,pLight->GetLightColor());
				GetRenderSystem()->SetValue(pUniformPosESRadius,vPosESRadius);
		
				float cameraToCenter = vPosES.length();
				if (cameraToCenter < pPointLight->GetRadius())
				{
					m_pPointLight->SetCullMode(CULL_FACE_SIDE_FRONT);	
				}
				else
				{
					m_pPointLight->SetCullMode(CULL_FACE_SIDE_BACK);
				}

				UnitSphere::Render(m_pPointLight.get(),pPointLight->GetSceneNode()->GetPos(),pPointLight->GetRadius());
			}

			GetRenderContext()->SetCurLight(NULL);
		}

		RenderQueue* pRenderQueue = m_pScene->GetRenderQueue();
		{
			RENDER_PROFILE(RL_Trans);
			pRenderQueue->RenderObjList(RL_Particle);
		}
	}

	void DeferredLightPass::Shoutdown()
	{
		m_pDirLight = NULL;
		m_pPointLight = NULL;
		m_pAmbientLight = NULL;
	}

}

