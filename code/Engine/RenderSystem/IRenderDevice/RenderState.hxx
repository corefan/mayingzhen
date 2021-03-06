#include "RenderState.h"


namespace ma
{

	RasterizerState::RasterizerState()
	{
		m_fConstantBias = 0;
		m_fSlopeScaleBias = 0;
		m_eCullMode = CULL_FACE_SIDE_BACK;
		m_eFillMode = FILL_SOLID;
		m_bScissorTest = false;
	}

	void RasterizerState::RegisterAttribute()
	{
		ENUM_ATTRIBUTE(RasterizerState, "CullMode", m_eCullMode, CULL_MODE, strCullMode, CULL_FACE_SIDE_BACK, AM_DEFAULT);
	}

	RefPtr<RasterizerState> CreateRasterizerState()
	{
		return GetRenderDevice()->CreateRasterizerState();
	}

	DepthStencilState::DepthStencilState()
	{
		m_bDepthWrite = true;
		m_eDepthCheckMode = CMPF_LESS_EQUAL;
		m_bStencil = false;
		m_eStencilfunc = CMPF_ALWAYS_PASS;
		m_eStencilPass = SOP_KEEP;
		m_eStencilFail = SOP_KEEP;
		m_eDepthFailOp = SOP_KEEP;
		//m_nStencilRefValue = -1;
		m_nStencilMask = -1;
		m_nStencilWriteMask = -1;
	}

	void DepthStencilState::RegisterAttribute()
	{
		ATTRIBUTE(DepthStencilState, "DepthWrite", m_bDepthWrite, bool, true, AM_DEFAULT);
		ENUM_ATTRIBUTE(DepthStencilState, "DepthCheckMode", m_eDepthCheckMode, CompareFunction, strCompareFunction, CMPF_LESS_EQUAL, AM_DEFAULT);
		ATTRIBUTE(DepthStencilState, "Stencil", m_bStencil, bool, false, AM_DEFAULT);
		ENUM_ATTRIBUTE(DepthStencilState, "Stencilfunc", m_eStencilfunc, CompareFunction, strCompareFunction, CMPF_ALWAYS_PASS, AM_DEFAULT);
		ENUM_ATTRIBUTE(DepthStencilState, "StencilPass", m_eStencilPass, StencilOperation, strStencilOperation, SOP_KEEP, AM_DEFAULT);
		ENUM_ATTRIBUTE(DepthStencilState, "StencilFail ", m_eStencilFail, StencilOperation, strStencilOperation, SOP_KEEP, AM_DEFAULT);
		ENUM_ATTRIBUTE(DepthStencilState, "DepthFailOp", m_eDepthFailOp, StencilOperation, strStencilOperation, SOP_KEEP, AM_DEFAULT);
		//ATTRIBUTE(DepthStencilState, "StencilRefValue", m_nStencilRefValue, uint32, -1, AM_DEFAULT);
		ATTRIBUTE(DepthStencilState, "StencilMask", m_nStencilMask, uint32, -1, AM_DEFAULT);
		ATTRIBUTE(DepthStencilState, "WriteMask", m_nStencilWriteMask, uint32, -1, AM_DEFAULT);
	}

	RefPtr<DepthStencilState> CreateDepthStencilState()
	{
		return GetRenderDevice()->CreateDepthStencilState();
	}

	BlendState::BlendState()
	{
		m_bColorWrite = true;
		m_eBlendMode = BM_OPATICY;
	}

	void BlendState::RegisterAttribute()
	{
		ATTRIBUTE(BlendState, "ColorWrite", m_bColorWrite, bool, true, AM_DEFAULT);
		ENUM_ATTRIBUTE(BlendState, "BlendMode", m_eBlendMode, BLEND_MODE, strBlendMode, BM_OPATICY, AM_DEFAULT);
	}

	RefPtr<BlendState> CreateBlendState()
	{
		return GetRenderDevice()->CreateBlendState();
	}

}
