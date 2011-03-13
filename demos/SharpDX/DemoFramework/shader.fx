SamplerState lightDepthSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};
Texture2D lightDepthMap;

cbuffer scene
{
	matrix View;
	matrix Projection;
	matrix ViewInverse;
	matrix LightView;
	matrix LightProjection;
	float3 LightPosition;
}

struct VS_IN
{
	float4 Pos : POSITION;
	float3 Normal : NORMAL;
	float4 World0 : WORLD0;
    float4 World1 : WORLD1;
    float4 World2 : WORLD2;
	float4 World3 : WORLD3;
	float4 Color : COLOR;
};

struct VS_OUT
{
    float4 Pos : SV_POSITION;
	float3 light : TEXCOORD0;
	float3 Normal : TEXCOORD1;
	float4 LPos : TEXCOORD2;
	float4 Color : TEXCOORD3;
};

float4 shadowGenVS(VS_IN input) : SV_POSITION
{
	float4x4 world = float4x4(input.World0, input.World1, input.World2, input.World3);
    float4 Pw = mul(input.Pos,world);
    float4 Pl = mul(LightView,Pw);  // "P" in light coords
	Pl = mul(LightProjection,Pl);
	return Pl;
}

VS_OUT VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

	float4x4 world = float4x4(input.World0, input.World1, input.World2, input.World3);
	output.Pos = mul(input.Pos, world);
	output.light = LightPosition - output.Pos.xyz;
	output.Pos = mul(View, output.Pos);
    output.Pos = mul(Projection, output.Pos);

	output.Normal = mul(input.Normal, world).xyz;
	output.Color = input.Color;

    float4 Pw = mul(input.Pos, world);
    float4 Pl = mul(LightView,Pw);
	output.LPos = mul(LightProjection,Pl);

    return output;
}

float GetShadowAmount(float4 shadowCoord)
{
	float2 texCoords = (shadowCoord.xy + 1) / 2;
	texCoords.y = 1 - texCoords.y;

	if (saturate(texCoords.x) == texCoords.x && saturate(texCoords.y) == texCoords.y)
	{
		float shadowBias = 0.002;
		float depth = shadowCoord.z/shadowCoord.w - shadowBias;

		float range = 0.00125;
		float4 s;
		s.r = lightDepthMap.Sample(lightDepthSampler, texCoords + float2(range, range)).x;
		s.g = lightDepthMap.Sample(lightDepthSampler, texCoords + float2(range, -range)).x;
		s.b = lightDepthMap.Sample(lightDepthSampler, texCoords + float2(-range, range)).x;
		s.a = lightDepthMap.Sample(lightDepthSampler, texCoords + float2(-range, -range)).x;
		//float4 s = lightDepthMap.Gather(lightDepthSampler, texCoords); // PS 4.1

		float4 inLight = depth < s;
		return 0.9 + dot(inLight, 0.25) * 0.1;
	}

	return 1;
}

float4 PS( VS_OUT input ) : SV_Target
{
	float3 normal = normalize(input.Normal);
	float3 light = normalize(input.light);

	float shade = 0.5+0.5*pow(saturate(dot(light, normal)), 2.0);
	shade *= GetShadowAmount(input.LPos);
	return float4(input.Color.rgb * shade, input.Color.a);
}

float4 PS_NoShadow( VS_OUT input ) : SV_Target
{
	float3 normal = normalize(input.Normal);
	float3 light = normalize(input.light);

	float shade = 0.5+0.5*pow(saturate(dot(light, normal)), 2.0);
	return float4(input.Color.rgb * shade, input.Color.a);
}

technique10 Render
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, shadowGenVS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( NULL );
	}

    pass P1
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }

    pass P2
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_NoShadow() ) );
    }
}
