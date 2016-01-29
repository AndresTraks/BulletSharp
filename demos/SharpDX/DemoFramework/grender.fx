SamplerState defaultSampler
{
    Filter = MIN_MAG_MIP_POINT;
};
SamplerState shadowSampler
{
    Filter = MIN_MAG_LINEAR_MIP_POINT;
	AddressU = Clamp;
	AddressV = Clamp;
};
SamplerState blurSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D lightBuffer;
Texture2D normalBuffer;
Texture2D diffuseBuffer;
Texture2D depthMap;
Texture2D lightDepthMap;

matrix OverlayViewProjection;
float4 SunLightDirection;

float ViewportWidth;
float ViewportHeight;
float4 ViewParameters; //TanHalfFOVX, TanHalfFOVY, ProjectionA, ProjectionB

struct SCREEN_VS_OUT
{
	float4 Pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

SCREEN_VS_OUT Screen_VS(uint id : SV_VertexID)
{
	SCREEN_VS_OUT output;

	// Construct full-screen triangle
	output.texCoord = float2((id << 1) & 2, id & 2);
	output.Pos = float4(output.texCoord * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);

	return output;
}

float GetShadowTerm(float2 texCoord)
{
	float depthSample = depthMap.Sample(defaultSampler, texCoord).x;
	float2 projection = ViewParameters.zw;
	float linearDepth = projection.y / (depthSample - projection.x);

	float2 screenPos = (texCoord * float2(2, -2)) + float2(-1, 1); // from 0...1 to -1...1
	float2 tanHalfFOV = ViewParameters.xy;
	float4 viewSpacePosition = float4(linearDepth * float3(screenPos * tanHalfFOV, 1), 1);
	float3 worldPosition = mul(ViewInverse, viewSpacePosition).xyz;
	float4 lightScreenPosition = mul(LightViewProjection, float4(worldPosition, 1));

	float2 lightScreenPos = lightScreenPosition.xy / lightScreenPosition.w;

	if (lightScreenPos.x >= -1 && lightScreenPos.x <= 1 && lightScreenPos.y >= -1 && lightScreenPos.y <= 1)
	{
		float lightDepthActual = lightScreenPosition.z / lightScreenPosition.w;
		lightScreenPos = (lightScreenPos - float2(-1, 1)) * float2(0.5, -0.5); // from -1...1 to 0...1
		float lightDepthSample = lightDepthMap.Sample(shadowSampler, lightScreenPos).x;

		float shadowMul = ((lightDepthActual - lightDepthSample) > 0.00006) ? 0.8 : 1;
		return shadowMul;
	}

	return 1;
}

float4 PS(SCREEN_VS_OUT input) : SV_Target
{
	float3 diffuseSample = diffuseBuffer.Sample(defaultSampler, input.texCoord).rgb;
	float4 normalSample = normalBuffer.Sample(defaultSampler, input.texCoord);

	// Skip lighting if normal.w == 0
	if (normalSample.w == 0)
	{
		return float4(diffuseSample, 1);
	}

	float3 normal = normalize((normalSample.xyz - 0.5) * 2); // from 0...1 to -1...1

	// Ambient term
	float3 ambientColor = float3(0.4, 0.4, 0.4);
	float3 ambient = ambientColor * diffuseSample;

	float4 lightSample = lightBuffer.Sample(defaultSampler, input.texCoord);
	float3 dirLight = 0.5 * saturate(dot(normal, -SunLightDirection.xyz)) * diffuseSample;

	dirLight *= GetShadowTerm(input.texCoord);

	// Debugging
	//return float4(normal, 1);

	return float4(lightSample.xyz + ambient + dirLight, 1);
}


float4 Blur_PS(SCREEN_VS_OUT input) : SV_Target
{
	float radius = 2;
	float dx = radius / ViewportWidth;
	float dy = radius / ViewportHeight;
	float dx2 = dx + dx;
	float dy2 = dy + dy;

	float4 diffuse = 0;
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord);
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord + float2(-dx, 0));
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord + float2(-dx2, 0));
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord + float2(+dx, 0));
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord + float2(+dx2, 0));
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord + float2(0, -dy));
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord + float2(0, -dy2));
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord + float2(0, +dy));
	diffuse += diffuseBuffer.Sample(blurSampler, input.texCoord + float2(0, +dy2));
	return diffuse / 9;
}

float4 PostProcess_PS(SCREEN_VS_OUT input) : SV_Target
{
	float3 diffuse = diffuseBuffer.Sample(defaultSampler, input.texCoord).xyz;
	float3 diffuseBlurred = normalBuffer.Sample(defaultSampler, input.texCoord).xyz;

	float depth = depthMap.Sample(defaultSampler, input.texCoord).x;
	float2 projection = ViewParameters.zw;
	float linearDepth = projection.y / (depth - projection.x);
	float focus = 50;
	float radius = abs(linearDepth - focus);
	radius /= 20;

	// Debugging
	//return float4(diffuseBlurred, 1);

	return float4(lerp(diffuse, diffuseBlurred, saturate(radius)), 1);
}


SCREEN_VS_OUT Overlay_VS(uint id : SV_VertexID)
{
	SCREEN_VS_OUT output;

	// Construct overlay quad
	output.texCoord = 0.5 * float2((id << 1) & 2, id & 2);
	output.Pos = float4(output.texCoord * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);
	output.Pos = mul(output.Pos, OverlayViewProjection);

	return output;
}

float4 Overlay_PS(SCREEN_VS_OUT input) : SV_Target
{
	return diffuseBuffer.Sample(defaultSampler, input.texCoord);
}

technique10 DeferredShader
{
	pass DeferredShader
	{
		SetVertexShader( CompileShader( vs_4_0, Screen_VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
	}

	pass Blur
	{
		SetVertexShader( CompileShader( vs_4_0, Screen_VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, Blur_PS() ) );
	}

	pass PostProcess
	{
		SetVertexShader( CompileShader( vs_4_0, Screen_VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PostProcess_PS() ) );
	}

	pass Overlay
	{
		SetVertexShader( CompileShader( vs_4_0, Overlay_VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, Overlay_PS() ) );
	}
}
