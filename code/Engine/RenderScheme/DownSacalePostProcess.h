#ifndef _DownScalePostProcess__H__
#define _DownScalePostProcess__H__

namespace ma
{
	class DownScalePostProcess : public PostProcess
	{
	public:
		DownScalePostProcess(Scene* pScene,Texture* pInputTex, Texture* pOutputTex,int nScale = 2);

		~DownScalePostProcess();

		virtual void		Init();

		virtual void		Reset(int nWidth, int nHeight);

		virtual void		Shutdown();

		virtual void		Render();

	private:
		void				GetSampleOffsets4x4(int width, int height,Vector4 texCoordOffSet[],int nArray);

	private:
		RefPtr<Technique>	m_DownScaleTech;

		int					m_nScale;
	};
}



#endif

