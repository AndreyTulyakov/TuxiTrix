cbuffer cbPerObject
{
	float4x4 FinalMatrix;
	float4 ModulationColor;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float2 TextureCoord  : TEXCOORD;
};


VS_OUTPUT VS(float4 pPosition : POSITION,float2 inTexCoord : TEXCOORD)
{
    VS_OUTPUT output;
	
    output.Position = mul(pPosition, FinalMatrix);
    output.TextureCoord = inTexCoord;

    return output;
}


float4 PS(VS_OUTPUT input) : SV_TARGET
{	
	float4 OutputColor=ObjTexture.Sample( ObjSamplerState, input.TextureCoord ) * ModulationColor;

    return OutputColor;
}