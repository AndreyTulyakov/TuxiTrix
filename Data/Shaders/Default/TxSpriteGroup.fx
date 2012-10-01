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
	float2 pTexCoord	: TEXCOORD;
	float4 pColor 		: RGBA;
};

struct VS_OUTPUT
{
	float4 Position		: SV_POSITION;
	float2 TexCoord		: TEXCOORD;
	float4 Color 		: COLOR0;
};


VS_OUTPUT VS( VS_INPUT input)
{
    VS_OUTPUT output;
	

	// Rotating
	
	float s=sin(input.pRotation[2]);
	float c=cos(input.pRotation[2]);
	
	float posX=input.pPosition[0];
	float posY=input.pPosition[1];
	
	input.pPosition[0]= posX*c + posY*s;
	input.pPosition[1]=-posX*s + posY*c;

	
	float4 ResultPosition;
	ResultPosition[0] = (input.pPosition[0]*input.pScale+input.pRotation[0]);
	ResultPosition[1] = (input.pPosition[1]*input.pScale+input.pRotation[1]);
	ResultPosition[2] = 0.0f;
	ResultPosition[3] = 1.0f;
	
	
	//  *input.pScale
	input.pPosition[0] = (input.pPosition[0]*input.pScale+input.pRotation[0]);
	input.pPosition[1] = (input.pPosition[1]*input.pScale+input.pRotation[1]);

    output.Position 			= mul(input.pPosition, FinalMatrix);
    output.TexCoord 			= input.pTexCoord;
	output.Color				= input.pColor;

    return output;
}


float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 OutputColor=ObjTexture.Sample( ObjSamplerState, input.TexCoord ) * input.Color;

    return OutputColor;
}