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
matrix ViewProjection;
matrix InverseProjection;
matrix InverseView;
matrix LightInverseViewProjection;
float4 LightPosition;
float4 EyePosition;
float4 EyeZAxis;
float TanHalfFOVX;
float TanHalfFOVY;
float ProjectionA;
float ProjectionB;

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
	float4 lightSample = lightBuffer.Sample(defaultSampler, input.texCoord);
	float4 normalSample = normalBuffer.Sample(defaultSampler, input.texCoord);
	float3 diffuseSample = diffuseBuffer.Sample(defaultSampler, input.texCoord).rgb;
	float depthSample = depthMap.Sample(defaultSampler, input.texCoord).x;
	float lightDepthSample = lightDepthMap.Sample(defaultSampler, input.texCoord).x;

	// from 0...1 to -1...1; also take advantage of mad (mul + add)
	float2 screenPos = (input.texCoord * float2(2,-2)) + float2(-1,1);

	float linearDepth = ProjectionB / (depthSample - ProjectionA);

	float4 viewSpacePosition = float4(
		linearDepth * screenPos.x*TanHalfFOVX,
		linearDepth * screenPos.y*TanHalfFOVY,
		linearDepth, 1);
	float4 worldPosition = mul(viewSpacePosition, InverseView);

	// Project the view ray onto the camera's z-axis
	//float viewZDist = dot(EyeZAxis.xyz, viewSpacePosition);
	//float3 worldPosition = EyePosition.xyz + viewSpacePosition * (linearDepth/viewZDist);

	float3 light = LightPosition.xyz - worldPosition;
	//float3 light = normalize(LightPosition.xyz);
	light = normalize(light);
	float3 normal = normalize((normalSample.xyz - 0.5) * 2); // from 0...1 to -1...1
	float3 vhalf = normalize(light + EyePosition);

	float3 specularMaterial = float3(0.8, 0.8, 1.0);
	//float3 specularMaterial = float3(1.0, 1.0, 1.0);
	float diffuse = 0.5 + 0.5 * dot(normal, light);
    float specular = saturate(dot(normal, vhalf));
    specular = 0.3f * pow(specular, 16);

	//float shade *= GetShadowAmount(input.LPos);
	//diffuse *= shade;

	return float4(diffuse * diffuseSample + specular * specularMaterial, 1);
}

VS_OUT Overlay_VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

	output.Pos = mul(float4(input.Pos,1), OverlayViewProjection);
	output.texCoord = input.texCoord;

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
