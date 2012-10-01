Texture2D ObjTexture;
SamplerState ObjSamplerState;

cbuffer ConstantBuffer
{
	float4x4 FinalMatrix;
};


struct VS_INPUT
{
	float4 pPosition 	: POSITION;
	float3 pRotation 	: ROTATION;
	float  pScale 		: SCALE;
	float2 pTextureCoordinates : TEXCOORD;
	float4 pColor 		: RGBA;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float2 TextureCoordinates  : TEXCOORD;
	float4 Color : COLOR0;
};


VS_OUTPUT VS( VS_INPUT input)
{
    VS_OUTPUT output;
	
	/*
	// Rotating
	float s=sin(pRotation[2]);
	float c=cos(pRotation[2]);
	
	float posX=pPosition[0];
	float posY=pPosition[1];
	
	pPosition[0]= posX*c + posY*s;
	pPosition[1]=-posX*s + posY*c;

	pPosition[0]*=pScale;
	pPosition[1]*=pScale;
	*/
	// Absolut coordinates + vertex offset
	
	input.pPosition[0]+=input.pRotation[0];
	input.pPosition[1]+=input.pRotation[1];
	

    output.Position = mul(input.pPosition, FinalMatrix);
    output.TextureCoordinates = input.pTextureCoordinates;
	output.Color=input.pColor;

    return output;
}


float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 OutputColor=ObjTexture.Sample( ObjSamplerState, input.TextureCoordinates ) * input.Color;

    return OutputColor;
}