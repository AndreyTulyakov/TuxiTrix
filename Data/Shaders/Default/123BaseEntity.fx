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


VS_OUTPUT VS(float4 pPosition : POSITION,float2 inTexCoord : TEXCOORD,float4 inColor : RGBA)
{
    VS_OUTPUT output;
	
    output.Position = mul(pPosition, FinalMatrix);
    output.TextureCoord = inTexCoord;
	output.Color=inColor;
	
    return output;
}

float4 Blur(VS_OUTPUT input)
{
	float4 OutputColor=ObjTexture.Sample( ObjSamplerState, input.TextureCoord );
	
	OutputColor+=ObjTexture.Sample( ObjSamplerState, input.TextureCoord+float2(0.0f,0.01f) );
	OutputColor+=ObjTexture.Sample( ObjSamplerState, input.TextureCoord+float2(0.0f,-0.01f) );
	OutputColor+=ObjTexture.Sample( ObjSamplerState, input.TextureCoord+float2(0.01f,0.0f) );
	OutputColor+=ObjTexture.Sample( ObjSamplerState, input.TextureCoord+float2(-0.01f,0.0f) );
	
	OutputColor+=ObjTexture.Sample( ObjSamplerState, input.TextureCoord+float2(-0.01f,-0.01f) );
	OutputColor+=ObjTexture.Sample( ObjSamplerState, input.TextureCoord+float2(0.01f,-0.01f) );
	OutputColor+=ObjTexture.Sample( ObjSamplerState, input.TextureCoord+float2(0.01f,0.01f) );
	OutputColor+=ObjTexture.Sample( ObjSamplerState, input.TextureCoord+float2(-0.01f,0.01f) );
	
	OutputColor/=9.0f;
	
	return OutputColor;
}


float4 NightVisionPixel(float4 color,float Sensitivity, float2 PixelPosition)
{
	color[1]+=color[0]*color[2];
	color[1]/=2;
	
	if(color[1]>1.0f-Sensitivity) 
		color[1]*=1.2f;
		
	if(color[1]<1.0f-Sensitivity) 
		color[1]*=0.8f;
	
	if(color[1]>1.0f) 
		color[1]=1.0f;

	color[0]=0.0f;
	color[2]=0.0f;
	

	int posY=PixelPosition.y*197;
	
	if(posY%2==0)
	{
		color[0]*=0.9f;
		color[1]*=0.9f;
		color[2]*=0.9f;
	}
	else
	{
		color[0]*=1.1f;
		color[1]*=1.1f;
		color[2]*=1.1f;
	}
	
	return color;
}



float4 PS(VS_OUTPUT input) : SV_TARGET
{	
	float4 OutputColor=ObjTexture.Sample( ObjSamplerState, input.TextureCoord ) * input.Color;
	
	OutputColor=NightVisionPixel(OutputColor,0.9f,input.TextureCoord);
	
    return OutputColor;
}