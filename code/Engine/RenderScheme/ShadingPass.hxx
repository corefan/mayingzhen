#include "ShadingPass.h"
#include "HDRPostProcess.h"

namespace ma
{
	ShadingPass::ShadingPass(Scene* pScene)
		:RenderPass(pScene)
	{
		m_bIsHDRRending = false;
 	}

	void ShadingPass::Init()
	{
		m_pShadingTex = NULL;
		m_pHdrPostprocess = NULL;

		if (m_bIsHDRRending)
		{
			m_pShadingTex = GetRenderSystem()->CreateRenderTexture(-1,-1,PF_FLOAT16_RGBA);	

			RefPtr<Texture>	 pOutTagget = GetRenderSystem()->GetRenderTarget(0);

			m_pHdrPostprocess = new HDRPostProcess(m_pShadingTex.get(),pOutTagget.get());
			m_pHdrPostprocess->Init();
		}
	}

	void ShadingPass::RenderObjecList()
	{
		ColourValue cClearClor = GetRenderSystem()->GetClearColor();

		GetRenderSystem()->ClearBuffer(true,true,true,cClearClor, 1.0f, 0);

		RenderQueue* pRenderQueue = m_pScene->GetRenderQueue();

		{
			RENDER_PROFILE(RL_Solid);
			pRenderQueue->RenderObjList(RL_Solid);
		}

		{
			RENDER_PROFILE(RL_TerrainBody);
			pRenderQueue->RenderObjList(RL_TerrainBody);
		}

		{
			RENDER_PROFILE(RL_TerrainBorder);
			pRenderQueue->RenderObjList(RL_TerrainBorder);
		}

		{
			RENDER_PROFILE(RL_Trans);
			pRenderQueue->RenderObjList(RL_Trans);
		}

	}

	void ShadingPass::Render()
	{
		RENDER_PROFILE(ShadingPass);

		RefPtr<Texture> pPreTarget = NULL;
		if (m_bIsHDRRending)
		{
			pPreTarget = GetRenderSystem()->SetRenderTarget(m_pShadingTex.get());
		}

		RenderObjecList();

		if (m_bIsHDRRending)
		{
			GetRenderSystem()->SetRenderTarget(pPreTarget);

			m_pHdrPostprocess->Render();
		}
	}

	void ShadingPass::ShoutDown()
	{
		m_pShadingTex = NULL;
		SAFE_DELETE(m_pHdrPostprocess);
	}
}

