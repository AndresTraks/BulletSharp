SamplerState bufferSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};
Texture2D lightBuffer;
Texture2D normalBuffer;
Texture2D diffuseBuffer;

SamplerState depthSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};
Texture2D depthMap;
Texture2D lightDepthMap;

matrix ViewProjection;
matrix InverseProjection;
matrix InverseView;
matrix LightInverseViewProjection;
float4 LightPosition;

struct VS_IN
{
	float3 Pos : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUT
{
    float4 Pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

VS_OUT VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

	output.Pos = mul(ViewProjection, float4(input.Pos,1));
	output.texCoord = input.texCoord;

	return output;
}

float4 PS( VS_OUT input ) : SV_Target
{
	float4 lightSample = lightBuffer.Sample(bufferSampler, input.texCoord);
	float4 normalSample = normalBuffer.Sample(bufferSampler, input.texCoord);
	float4 diffuseSample = diffuseBuffer.Sample(bufferSampler, input.texCoord);
	float depthSample = depthMap.Sample(depthSampler, input.texCoord).x;
	float lightDepthSample = lightDepthMap.Sample(depthSampler, input.texCoord).x;
	
	float4 projected = float4(input.texCoord.x * 2 - 1, (1 - input.texCoord.y) * 2 - 1, depthSample, 1);
	float4 worldPosition = mul(projected, InverseProjection);
	//worldPosition.xyz / worldPosition.w;
	worldPosition = mul(worldPosition, InverseView);

	//float3 light = normalize(LightPosition.xyz - worldPosition.xyz);
	float3 light = normalize(LightPosition.xyz);
	float3 normal = (normalSample.xyz - 0.5) * 2; // from 0...1 to -1...1 range
	float3 diffuse = diffuseSample.xyz;

	float shade = 0.5+0.5*saturate(dot(light, normal));
	//shade *= GetShadowAmount(input.LPos);
	diffuse *= shade;

	return float4(diffuse, 1);
}

technique10 Render
{
    pass P1
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
