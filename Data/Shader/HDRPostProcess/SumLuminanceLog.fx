float4 tex_coord_offset[2];

texture g_TextureSrc;

sampler g_SamplerSrc = sampler_state
{
	Texture = <g_TextureSrc>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
	AddressU = Clamp;
	AddressV = Clamp;
};



float2 TexCoordFromPos(float4 pos)
{
	float2 tex = pos.xy / 2;
	tex.y *= -1;
	tex += 0.5;
	return tex;
}

void SumLumVS(float4 pos : POSITION,
					out float4 oTex0 : TEXCOORD0,
					out float4 oTex1 : TEXCOORD1,
					out float4 oPos : POSITION)
{
	oPos = pos;

	float2 tex = TexCoordFromPos(pos);
	oTex0 = tex.xyxy + tex_coord_offset[0];
	oTex1 = tex.xyxy + tex_coord_offset[1];
}

float4 SumLum4x4LogPS(float4 iTex0 : TEXCOORD0,
						float4 iTex1 : TEXCOORD1) : COLOR
{
	const float3 RGB_TO_LUM = float3(0.2126f, 0.7152f, 0.0722f);
	float4 tex[2] = { iTex0, iTex1 };

	float s = 0;
	for (int i = 0; i < 2; ++ i)
	{
		s += log( dot( tex2D(g_SamplerSrc, tex[i].xy).rgb, RGB_TO_LUM) + 0.001f);
		s += log( dot( tex2D(g_SamplerSrc, tex[i].zw).rgb, RGB_TO_LUM) + 0.001f);
	}

	return s / 4;
}	
	
technique SumLumLog
{
	pass P0
	{
		VertexShader = compile vs_3_0 SumLumVS();
		PixelShader = compile ps_3_0 SumLum4x4LogPS();
		
		CullMode = cw;
	}
}