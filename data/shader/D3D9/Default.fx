float4x4 u_worldViewProjectionMatrix : worldviewprojection;

#define MAX_SKIN_MATRIX 60
#define MAX_BLEND_BONE 4
float4x3    u_matrixPalette[MAX_SKIN_MATRIX] : WORLDMATRIXARRAY;

texture u_diffuseTexture;
sampler g_SamplerSrcDiffuse = sampler_state
{
	Texture = <u_diffuseTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};

void ShadingVS( float4 pos : POSITION,
				float2 texcoord : TEXCOORD0,
				out float4 oPos : POSITION,
				out float2 oTexCoord: TEXCOORD0)
{
	oPos = mul( pos, u_worldViewProjectionMatrix );
	oTexCoord = texcoord;
}

float4 ShadingPS( float2 texcoord : TEXCOORD0) : COLOR0
{
	float4 srcDiffuse = tex2D(g_SamplerSrcDiffuse, texcoord);
	
	//return float4(1.0f,0.0f,0.0f,1.0f);
	return float4( srcDiffuse.rgb, 1.0f);
}


void SkinPos( float3 pos ,
			  float4 BlendWeights , 
			  int4 BlendIndices,
			  out float3 wPos)
{
	wPos = 0;
	int   IndexArray[4]   = (int[4])BlendIndices; 
	float WeightArray[4] = (float[4])BlendWeights;
	for (int iBone = 0; iBone < MAX_BLEND_BONE; ++iBone)
	{
		wPos += mul(float4(pos,1), u_matrixPalette[IndexArray[iBone]]).xyz * WeightArray[iBone];
	}
}

void SkinShadingVS( float3 pos : POSITION,
					float4 BlendWeights :BLENDWEIGHT, 
					int4 BlendIndices :BLENDINDICES,
					float2 texcoord : TEXCOORD0,
					out float4 oPos : POSITION,
					out float2 oTexCoord: TEXCOORD0)
{
	float3 wPos = 0;

	SkinPos(pos,BlendWeights,BlendIndices,wPos);
	
	oPos = mul( float4(wPos.xyz, 1.0f), u_worldViewProjectionMatrix );
	oTexCoord = texcoord;
}



technique Default
{
	pass P0
	{
		VertexShader = compile vs_2_0 ShadingVS();
		PixelShader = compile ps_2_0 ShadingPS();
	}
};


technique DefaultSkin
{
	pass P0
	{
		VertexShader = compile vs_2_0 SkinShadingVS();
		PixelShader = compile ps_2_0 ShadingPS();
	}
};