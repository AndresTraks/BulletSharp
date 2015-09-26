SamplerState defaultSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};

Texture2D lightBuffer;
Texture2D normalBuffer;
Texture2D diffuseBuffer;

Texture2D depthMap;
Texture2D lightDepthMap;

matrix OverlayViewProjection;
matrix InverseProjection;
matrix InverseView;
matrix LightInverseViewProjection;
float4 LightPosition;
float4 EyePosition;
float TanHalfFOVX;
float TanHalfFOVY;
float ProjectionA;
float ProjectionB;

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

VS_OUT VS(uint id : SV_VertexID)
{
	VS_OUT output = (VS_OUT)0;

	// Construct full-screen triangle
	output.texCoord = float2((id << 1) & 2, id & 2);
	output.Pos = float4(output.texCoord * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);

	return output;
}

float4 PS( VS_OUT input ) : SV_Target
{
	float4 lightSample = lightBuffer.Sample(defaultSampler, input.texCoord);
	float4 normalSample = normalBuffer.Sample(defaultSampler, input.texCoord);
	float3 diffuseSample = diffuseBuffer.Sample(defaultSampler, input.texCoord).rgb;
	float depthSample = depthMap.Sample(defaultSampler, input.texCoord).x;
	float lightDepthSample = lightDepthMap.Sample(defaultSampler, input.texCoord).x;

	// from 0...1 to -1...1
	float2 screenPos = (input.texCoord * float2(2,-2)) + float2(-1,1);

	float linearDepth = ProjectionB / (depthSample - ProjectionA);

	float4 viewSpacePosition = float4(
		linearDepth * screenPos.x*TanHalfFOVX,
		linearDepth * screenPos.y*TanHalfFOVY,
		linearDepth, 1);
	float3 worldPosition = mul(viewSpacePosition, InverseView).xyz;

	float3 normal = normalize((normalSample.xyz - 0.5) * 2); // from 0...1 to -1...1
	float3 lightDirection = normalize(LightPosition.xyz - worldPosition);
	float3 viewDirection = normalize(EyePosition.xyz - worldPosition);

	// Ambient term
	float3 ambientColor = 0.15 * diffuseSample;//float3(1,1,1);
	float3 ambient = ambientColor;

	// Diffuse term
	float3 diffuse = saturate(dot(normal, lightDirection)) * diffuseSample;

	// Specular term
	float3 specularColor = float3(1.0, 1.0, 1.0);
	float specularIntensity = saturate(dot(reflect(-lightDirection, normal), viewDirection));
	specularIntensity = pow(specularIntensity, 64);
	float3 specular = specularIntensity * specularColor;

	//float shade *= GetShadowAmount(input.LPos);
	//diffuse *= shade;

	// Debugging
	//return float4(worldPosition * 0.01 + 0.25, 1);
	//return float4(normal, 1);

	return float4(ambient + diffuse + 0.2 * specular, 1);
}

VS_OUT Overlay_VS(uint id : SV_VertexID)
{
	VS_OUT output = (VS_OUT)0;

	// Construct overlay quad
	output.texCoord = 0.5 * float2((id << 1) & 2, id & 2);
	output.Pos = float4(output.texCoord * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);
	output.Pos = mul(output.Pos, OverlayViewProjection);

	return output;
}

float4 Overlay_PS( VS_OUT input ) : SV_Target
{
	return diffuseBuffer.Sample(defaultSampler, input.texCoord);
}

technique10 Render
{
	pass P1
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
	}

	pass Overlay
	{
		SetVertexShader( CompileShader( vs_4_0, Overlay_VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, Overlay_PS() ) );
	}
}
