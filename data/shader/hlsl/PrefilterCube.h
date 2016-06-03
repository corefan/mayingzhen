

cbuffer ObjectVS : register(b5)
{
	int face;
	float roughness;
}


textureCUBE skybox_cube_tex : register(t1);
SamplerState skybox_sampler : register(s1);

float3 ToDir(int face, float2 xy)
{
	float3 dir;
	if (0 == face)
	{
		dir.x = +1;
		dir.yz = 1 - xy.yx * 2;
	}
	else if (1 == face)
	{
		dir.x = -1;
		dir.y = 1 - xy.y * 2;
		dir.z = xy.x * 2 - 1;
	}
	else if (2 == face)
	{
		dir.xz = xy.xy * 2 - 1;
		dir.y = +1;
	}
	else if (3 == face)
	{
		dir.x = xy.x * 2 - 1;
		dir.y = -1;
		dir.z = 1 - xy.y * 2;
	}
	else if (4 == face)
	{
		dir.x = xy.x * 2 - 1;
		dir.y = 1 - xy.y * 2;
		dir.z = +1;
	}
	else
	{
		dir.xy = 1 - xy.xy * 2;
		dir.z = -1;
	}

	return normalize(dir);
}

uint ReverseBits(uint bits)
{
	bits = (bits << 16) | (bits >> 16);
	bits = ((bits & 0x55555555) << 1) | ((bits & 0xAAAAAAAA) >> 1);
	bits = ((bits & 0x33333333) << 2) | ((bits & 0xCCCCCCCC) >> 2);
	bits = ((bits & 0x0F0F0F0F) << 4) | ((bits & 0xF0F0F0F0) >> 4);
	bits = ((bits & 0x00FF00FF) << 8) | ((bits & 0xFF00FF00) >> 8);
	return bits;
}

float RadicalInverseVdC(uint bits)
{
	return ReverseBits(bits) * 2.3283064365386963e-10f; // / 0x100000000
}

float2 Hammersley2D(uint i, uint N)
{
	return float2(float(i) / N, RadicalInverseVdC(i));
}

float3 ImportanceSampleLambert(float2 xi)
{
	const float PI = 3.1415926f;

	float phi = 2 * PI * xi.x;
	float cos_theta = sqrt(1 - xi.y);
	float sin_theta = sqrt(1 - cos_theta * cos_theta);
	return float3(sin_theta * cos(phi), sin_theta * sin(phi), cos_theta);
}

float3 ImportanceSampleLambert(float2 xi, float3 normal)
{
	float3 h = ImportanceSampleLambert(xi);
	
	float3 up_vec = abs(normal.z) < 0.999f ? float3(0, 0, 1) : float3(1, 0, 0);
	float3 tangent = normalize(cross(up_vec, normal));
	float3 binormal = cross(normal, tangent);
	return tangent * h.x + binormal * h.y + normal * h.z;
}

float3 ImportanceSampleBP(float2 xi, float roughness)
{
	const float PI = 3.1415926f;

	float phi = 2 * PI * xi.x;
	float cos_theta = pow(1 - xi.y * (roughness + 1) / (roughness + 2), 1 / (roughness + 1));
	float sin_theta = sqrt(1 - cos_theta * cos_theta);
	return float3(sin_theta * cos(phi), sin_theta * sin(phi), cos_theta);
}

float3 ImportanceSampleBP(float2 xi, float roughness, float3 normal)
{
	float3 h = ImportanceSampleBP(xi, roughness);
	
	float3 up_vec = abs(normal.z) < 0.999f ? float3(0, 0, 1) : float3(1, 0, 0);
	float3 tangent = normalize(cross(up_vec, normal));
	float3 binormal = cross(normal, tangent);
	return tangent * h.x + binormal * h.y + normal * h.z;
}

float3 SampleCubeMap(float3 ReflectDir)
{
	return skybox_cube_tex.SampleLevel(skybox_sampler, ReflectDir, 0).xyz;

}

float4 PrefilterCubeDiffusePS(float2 tex : TEXCOORD0) : SV_Target
{
	float3 normal = ToDir(face, tex);

	float3 prefiltered_clr = 0;

	const uint NUM_SAMPLES = 1024;
	for (uint i = 0; i < NUM_SAMPLES; ++ i)
	{
		float2 xi = Hammersley2D(i, NUM_SAMPLES);
		float3 l = ImportanceSampleLambert(xi, normal);

		prefiltered_clr += skybox_cube_tex.SampleLevel(skybox_sampler, l, 0).xyz;
	}

	return float4(prefiltered_clr / NUM_SAMPLES, 1);
}

float4 PrefilterCubeSpecularPS(float2 tex : TEXCOORD0) : SV_Target
{
	float3 r = ToDir(face, tex);
	
	float3 normal = r;
	float3 view = r;
	float3 prefiltered_clr = 0;
	float total_weight = 0;

	const uint NUM_SAMPLES = 1024;
	for (uint i = 0; i < NUM_SAMPLES; ++ i)
	{
		float2 xi = Hammersley2D(i, NUM_SAMPLES);
		float3 h = ImportanceSampleBP(xi, roughness, normal);
		float3 l = -reflect(view, h);
		float n_dot_l = saturate(dot(normal, l));
		if (n_dot_l > 0)
		{
			prefiltered_clr += skybox_cube_tex.SampleLevel(skybox_sampler, l, 0).xyz;
			total_weight += n_dot_l;
		}
	}

	return float4(prefiltered_clr / max(1e-6f, total_weight), 1);
}

