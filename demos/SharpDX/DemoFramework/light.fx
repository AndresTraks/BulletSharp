SamplerState defaultSampler
{
	Filter = MIN_MAG_MIP_POINT;
};

Texture2D normalBuffer;
Texture2D depthBuffer;

matrix World;
float4 PositionRadius;
float4 Color;

matrix View;
matrix Projection;
matrix ViewInverse;
float ViewportWidth;
float ViewportHeight;
float4 EyePosition;
float4 ViewParameters; //TanHalfFOVX, TanHalfFOVY, ProjectionA, ProjectionB

float4 VS(float4 Pos : POSITION) : SV_POSITION
{
	return mul(Projection, mul(View, mul(World, Pos)));
}

float4 PS( float4 Pos : SV_POSITION ) : SV_Target0
{
	float2 texCoords = Pos.xy / float2(ViewportWidth, ViewportHeight);
	float depthSample = depthBuffer.Sample(defaultSampler, texCoords).x;

	float2 projection = ViewParameters.zw;
	float linearDepth = projection.y / (depthSample - projection.x);

	float2 screenPos = (texCoords * float2(2,-2)) + float2(-1,1); // from 0...1 to -1...1
	float2 tanHalfFOV = ViewParameters.xy;
	float4 viewSpacePosition = float4(linearDepth * float3(screenPos * tanHalfFOV, 1), 1);
	float3 worldPosition = mul(viewSpacePosition, ViewInverse).xyz;

	float3 normalSample = normalBuffer.Sample(defaultSampler, texCoords).xyz;
	float3 normal = normalize((normalSample.xyz - 0.5) * 2); // from 0...1 to -1...1

	float3 lightDirection = PositionRadius.xyz - worldPosition;
	float lightRadius = PositionRadius.w;
	//float lightDistance = lerp(0, maxDistance, lightDistance);
	float lightIntensity = 1 - (min(length(lightDirection), lightRadius) / lightRadius);
	lightIntensity = lightIntensity * lightIntensity; // square distance
	lightDirection = normalize(lightDirection);
	float3 viewDirection = normalize(EyePosition.xyz - worldPosition);

	float3 diffuse = saturate(dot(normal, lightDirection)) * Color;

	// Specular term
	float3 specularColor = 0.15 * Color;
	float specularIntensity = saturate(dot(reflect(-lightDirection, normal), viewDirection));
	specularIntensity = pow(specularIntensity, 64);
	float3 specular = specularIntensity * specularColor;

	// Debugging
	//return float4(depthSample, depthSample, depthSample, 1);
	//return float4(worldPosition, 1);
	//return float4(Color.xyz, 1);

	float3 light = diffuse + specular;
	light *= lightIntensity;
	return float4(light, 1);
}

technique10 Render
{
	pass Light
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
	}
}
