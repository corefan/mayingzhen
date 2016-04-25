#pragma once

#include "Engine/Material/Texture.h"

namespace ma
{
	class D3D11Texture : public Texture
	{
	public:
		D3D11Texture();

		D3D11Texture(int nWidth,int nHeight,PixelFormat format = PF_A8R8G8B8,TEXTURE_USAGE eUsage = USAGE_STATIC);

		~D3D11Texture();
		
		ID3D11ShaderResourceView* GetShaderResourceView() {return m_pD3D11ShaderResourceView;}

		ID3D11DepthStencilView* GetDepthStencilView() {return m_pDepthStencilView;}
		void SetDepthStencilView(ID3D11DepthStencilView* pView) {m_pDepthStencilView = pView;}	

		ID3D11RenderTargetView* GetRenderTargetView() {return m_pRenderTargetView;}	
		void SetRenderTargetView(ID3D11RenderTargetView* pView) {m_pRenderTargetView = pView;}

	private:
		virtual	bool			RT_CreateTexture();		

		virtual	bool			RT_CreateDepthStencil();		

		virtual	bool			SetLevelData(int level, const PixelBox& src);

		virtual bool			GenerateMipmaps();
		
	private:
		ID3D11Texture2D*			m_pD3D11Tex2D;

		ID3D11ShaderResourceView*	m_pD3D11ShaderResourceView;

		ID3D11DepthStencilView*		m_pDepthStencilView;

		ID3D11RenderTargetView*		m_pRenderTargetView;

		DXGI_FORMAT					m_descFormat;
	};

}

