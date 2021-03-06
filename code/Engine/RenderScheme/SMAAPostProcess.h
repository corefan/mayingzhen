#ifndef _SMAAPostProcess__H__
#define _SMAAPostProcess__H__

namespace ma
{
	class SMAAPostProcess : public PostProcess
	{
	public:
		SMAAPostProcess();

		~SMAAPostProcess();

		virtual void		Init();

		virtual void		Reset(Texture* pInput, Texture* pOutput);

		virtual void		Shutdown();

		virtual void		Render();

	private:
		RefPtr<Technique> m_pColorEdgeDetection;
		RefPtr<Technique> m_pBlendWeightCalculation;
		RefPtr<Technique> m_pNeiborhoodBlending;

		RefPtr<Texture>	m_pTexEdge;
		RefPtr<Texture>	m_pTexBlend;

		RefPtr<SamplerState> m_pAreadTex;
		RefPtr<SamplerState> m_pSreachTex;
	};
}



#endif

