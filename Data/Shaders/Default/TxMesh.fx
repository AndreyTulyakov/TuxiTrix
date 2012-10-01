
Texture2D ObjTexture;
SamplerState ObjSamplerState;
// ----------------------------------------------------------------------
cbuffer ConstantBuffer
{
	//float4x4
	matrix WorldMatrix;
    matrix FinalMatrix;

	float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float padding;
};

struct VS_INPUT
{
    float4 Position : POSITION;
    float2 TexCoord : TEXCOORD0;
    float4 Normal : NORMAL;
}
;
struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float2 TextureCoord  : TEXCOORD0;
    float3 Normal : NORMAL;
}
;
// ----------------------------------------------------------------------
float4 DrawTextureEdge(float4 inColor,float2 inTexCoord);


VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT Output;
    input.Position.w=1.0f;

    Output.Position = mul(input.Position, FinalMatrix);
    Output.TextureCoord = input.TexCoord;

	Output.Normal = mul(input.Normal, (float3x3)WorldMatrix);
	Output.Normal = normalize(Output.Normal);

    return Output;
}




float4 PS(VS_OUTPUT input) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;


    textureColor = ObjTexture.Sample( ObjSamplerState, input.TextureCoord );
    color = ambientColor;
    lightDir = -lightDirection;
    lightIntensity = saturate(dot(input.Normal, lightDir));


    if(lightIntensity > 0.0f)
    {
        color += (diffuseColor * lightIntensity);
    }
	
    color = saturate(color);
    color = color * textureColor;
	
	color=DrawTextureEdge(color,input.TextureCoord);

    return color;
}


float4 DrawTextureEdge(float4 inColor,float2 inTexCoord)
{
	float4 SuperColor=float4( inTexCoord.x, inTexCoord.y, 0.0f, 1.0f);	

	if(inTexCoord.x<0.03f) return SuperColor;
	if(inTexCoord.x>0.97f) return SuperColor;
	if(inTexCoord.y<0.03f) return SuperColor;
	if(inTexCoord.y>0.97f) return SuperColor;

	return inColor;
}