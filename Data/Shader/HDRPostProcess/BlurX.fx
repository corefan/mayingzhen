float2 src_tex_size;
float color_weight[8];
float tex_coord_offset[8];

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


void BlurXVS(float4 pos : POSITION,
					out float4 oTex0 : TEXCOORD0,
					out float4 oTex1 : TEXCOORD1,
					out float4 oTex2 : TEXCOORD2,
					out float4 oTex3 : TEXCOORD3,
					out float2 oOriTex : TEXCOORD4,
					out float4 oPos : POSITION)
{
	oPos = pos;

	float2 Tex0 = TexCoordFromPos(pos);
	float4 tex[4];
	for (int i = 0; i < 4; ++ i)
	{
		tex[i] = Tex0.xyxy + float4(tex_coord_offset[i * 2 + 0], 0, tex_coord_offset[i * 2 + 1], 0);
	}
	oTex0 = tex[0];
	oTex1 = tex[1];
	oTex2 = tex[2];
	oTex3 = tex[3];
	oOriTex = Tex0;
}

float4 CalcBlur(float4 iTex0, float4 iTex1, float4 iTex2, float4 iTex3, float2 offset)
{
	float4 color = float4(0, 0, 0, 1);
	float4 tex[4] = { iTex0, iTex1, iTex2, iTex3 };

	for (int i = 0; i < 4; ++ i)
	{
		tex[i] += offset.xyxy;
		color.rgb += tex2D(g_SamplerSrc, tex[i].xy).rgb * color_weight[i * 2 + 0];
		color.rgb += tex2D(g_SamplerSrc, tex[i].zw).rgb * color_weight[i * 2 + 1];
	}

	return color;
}

float4 BlurXPS(float4 iTex0 : TEXCOORD0,
				float4 iTex1 : TEXCOORD1,
				float4 iTex2 : TEXCOORD2,
				float4 iTex3 : TEXCOORD3,
				float2 iOriTex : TEXCOORD4) : COLOR
{
	float2 offset = float2((floor(iOriTex.x * src_tex_size.x) + 0.5f) * src_tex_size.y - iOriTex.x, 0);
	return CalcBlur(iTex0, iTex1, iTex2, iTex3, offset);
}


technique BlurX
{
	pass P0
	{
		VertexShader = compile vs_3_0 BlurXVS();
		PixelShader = compile ps_3_0 BlurXPS();
		
		CullMode = cw;
	}
}