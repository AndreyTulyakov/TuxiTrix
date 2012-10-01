cbuffer cbPerObject
{
	float4x4 FinalMatrix;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float2 TextureCoord  : TEXCOORD;
	float4 Color : COLOR0;
};

VS_OUTPUT VS(float4 inPos : POSITION,float2 inTexCoord : TEXCOORD,float4 inColor : RGBA)
{
    VS_OUTPUT output;
	
    output.Position = mul(inPos, FinalMatrix);
    output.TextureCoord = inTexCoord;
	output.Color=inColor;
	
    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 OutputColor=ObjTexture.Sample( ObjSamplerState, input.TextureCoord ) * input.Color;
	
    return OutputColor;
}