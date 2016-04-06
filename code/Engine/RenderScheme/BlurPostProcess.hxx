#include "BlurPostProcess.h"

namespace ma
{
	BlurPostProcess::BlurPostProcess(Scene* pScene)
		:PostProcess(pScene)
	{

	}

	BlurPostProcess::~BlurPostProcess()
	{
	}

	void BlurPostProcess::Init()
	{
		m_BlurXTech = CreateTechnique("BlurX","Blur/Blur","Blur/Blur","BLUR_X 1"); 
		m_BlurYTech = CreateTechnique("BlurY","Blur/Blur","Blur/Blur","BLUR_Y 1");
	}

	void BlurPostProcess::Reset()
	{
// 		PixelFormat eformat = m_pInputTex->GetFormat();
// 		m_BureTempTex = GetRenderSystem()->CreateRenderTexture(nWidth,nHeight,eformat);
// 
// 		Vector2 texSize = Vector2((float)nWidth, 1.0f / (float)nWidth);
// 
// 		std::vector<float> color_weight;
// 		std::vector<float> tex_coord_offset;
// 		CalSampleOffsetsGauss(8,1,nWidth,3.0f,color_weight,tex_coord_offset);
// 
// 		m_BlurXTech->SetParameter( "color_weight", Any(color_weight) );
// 		m_BlurXTech->SetParameter( "tex_coord_offset", Any(tex_coord_offset) );
// 		m_BlurXTech->SetParameter( "src_tex_size", Any(texSize) );
// 		m_BlurXTech->SetParameter( "g_SamplerSrc", Any(m_pInputTex) );
// 
// 
// 		texSize = Vector2((float)nHeight, 1.0f / (float)nHeight);
// 		CalSampleOffsetsGauss(8,1,nHeight,3.0f,color_weight,tex_coord_offset);
// 
// 		m_BlurYTech->SetParameter( "color_weight", Any(color_weight) );
// 		m_BlurYTech->SetParameter( "tex_coord_offset", Any(tex_coord_offset) );
// 		m_BlurYTech->SetParameter( "src_tex_size", Any(texSize) );
// 		m_BlurYTech->SetParameter( "g_SamplerSrc", Any(m_BureTempTex) );
	}


	void BlurPostProcess::Shutdown()
	{
		m_BlurXTech = NULL;
		m_BlurYTech = NULL;
	}

	void BlurPostProcess::Render()
	{
		RENDER_PROFILE(BlurPostProcess);

		/// x
		GetRenderSystem()->SetRenderTarget(m_BureTempTex);
		GetRenderSystem()->ClearBuffer(true,true,true,ColourValue::White,1.0f,0);
	
		ScreenQuad::Render(m_BlurXTech.get());


		/// y
		GetRenderSystem()->SetRenderTarget(m_pOutputTex);
		GetRenderSystem()->ClearBuffer(true,true,true,ColourValue::White,1.0f,0);

		ScreenQuad::Render(m_BlurYTech.get());
	}


	float BlurPostProcess::GaussianDistribution(float x, float y, float rho)
	{
		float g = 1.0f / sqrtf( 2.0f * Math::PI * rho * rho );
		g *= expf( -( x * x + y * y ) / ( 2 * rho * rho ) );

		return g;
	}

	void BlurPostProcess::CalSampleOffsetsGauss(int kernelRaidius, float multiplier,
		int texSize, float deviation,
		std::vector<float>& color_weight,
		std::vector<float>& tex_coord_offset)
	{
		color_weight.clear();
		tex_coord_offset.clear();
		color_weight.resize(kernelRaidius);
		tex_coord_offset.resize(kernelRaidius);

		std::vector<float> tmp_weights(kernelRaidius * 2, 0);
		std::vector<float> tmp_offset(kernelRaidius * 2, 0);

		float const tu = 1.0f / texSize;

		float sum_weight = 0;
		for (int i = 0; i < 2 * kernelRaidius; ++ i)
		{
			float weight = GaussianDistribution(static_cast<float>(i - kernelRaidius), 0, kernelRaidius / deviation);
			tmp_weights[i] = weight;
			sum_weight += weight;
		}
		for (int i = 0; i < 2 * kernelRaidius; ++ i)
		{
			tmp_weights[i] /= sum_weight;
		}

		// Fill the offsets
		for (int i = 0; i < kernelRaidius; ++ i)
		{
			tmp_offset[i]                  = static_cast<float>(i - kernelRaidius);
			tmp_offset[i + kernelRaidius] = static_cast<float>(i);
		}

		// Bilinear filtering taps
		// Ordering is left to right.
		for (int i = 0; i < kernelRaidius; ++ i)
		{
			float const scale = tmp_weights[i * 2] + tmp_weights[i * 2 + 1];
			float const frac = tmp_weights[i * 2] / scale;

			tex_coord_offset[i] = (tmp_offset[i * 2] + (1 - frac)) * tu;
			color_weight[i] = multiplier * scale;
		}
	}
}