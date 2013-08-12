// Uniforms
uniform float4x4 u_worldViewProjectionMatrix;

#ifdef SKIN
uniform float4x4 u_matrixPalette[SKIN_MATRIX_COUNT];
#endif



// Attributes
struct VS_IN
{
   float3 a_position : POSITION;

#ifdef SKIN   
   float4 a_blendWeights :BLENDWEIGHT;      
   int4   a_blendIndices :BLENDINDICES;
#endif   
 
#ifdef DIFFUSE   
   float2 a_texCoord0 : TEXCOORD0;
#endif

#ifdef COLOR   
   float4 a_color : COLOR0;
#endif

};


// Varyings
struct VS_OUT
{
   float4 v_position : POSITION;

#ifdef DIFFUSE    
   float2 v_texCoord : TEXCOORD0;
#endif  

#ifdef DeferredLight
   float2 v_defTc : TEXCOORD1;
#endif

   
#ifdef COLOR      
   float4 v_color : COLOR0;
#endif

   
};



#ifdef SKIN
void SkinPos(float3 pos,
           float4 a_blendWeights , 
           int4 	a_blendIndices,
           out float3 wPos)
{
    wPos = 0;
	wPos += mul(u_matrixPalette[a_blendIndices.x], float4(pos,1.0)).xyz * a_blendWeights.x;
	wPos += mul(u_matrixPalette[a_blendIndices.y], float4(pos,1.0)).xyz * a_blendWeights.y;
	wPos += mul(u_matrixPalette[a_blendIndices.z], float4(pos,1.0)).xyz * a_blendWeights.z;
	wPos += mul(u_matrixPalette[a_blendIndices.w], float4(pos,1.0)).xyz * a_blendWeights.w;  
}
#endif


VS_OUT main(VS_IN In)
{
    VS_OUT Out = (VS_OUT)0;
    
   float3 wPos = In.a_position;

#ifdef SKIN
   SkinPos(In.a_position,In.a_blendWeights,In.a_blendIndices,wPos);
#endif
   
    Out.v_position = mul(u_worldViewProjectionMatrix, float4(wPos,1)); // SetVertexShaderConstantF
    
#ifdef DIFFUSE      
    Out.v_texCoord = In.a_texCoord0;
#endif

#ifdef DeferredLight
   Out.v_defTc = Out.v_position.xy / Out.v_position.w;
   Out.v_defTc.y *= -1;
   Out.v_defTc = Out.v_defTc * 0.5f + 0.5f;
#endif   
    
#ifdef COLOR    
    Out.v_color = In.a_color;
#endif
    
    return Out;
}


