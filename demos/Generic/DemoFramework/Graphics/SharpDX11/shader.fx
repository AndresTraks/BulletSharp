cbuffer scene
{
	matrix View;
	matrix Projection;
	matrix ViewInverse;
	matrix LightViewProjection;
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
	float3 Normal : TEXCOORD0;
	float4 Color : TEXCOORD1;
};

struct PS_OUT_MRT
{
	float4 Normal : SV_Target0;
	float4 Diffuse : SV_Target1;
};

struct VS_DEBUG_IN
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
};

struct VS_DEBUG_OUT
{
	float4 Pos : SV_POSITION;
	float4 Color : TEXCOORD1;
};

struct PS_DEBUG_OUT_MRT
{
	float4 Normal : SV_Target0;
	float4 Diffuse : SV_Target1;
};

float4 shadowGenVS(VS_IN input) : SV_POSITION
{
	float4x4 world = float4x4(input.World0, input.World1, input.World2, input.World3);
	return mul(LightViewProjection, mul(input.Pos, world));  // Pos in light coords
}

VS_OUT VS(VS_IN input)
{
	VS_OUT output;

	float4x4 world = float4x4(input.World0, input.World1, input.World2, input.World3);
	output.Pos = mul(Projection, mul(View, mul(input.Pos, world)));

	output.Normal = mul(input.Normal, (float3x3)world);
	output.Color = input.Color;

	return output;
}

PS_OUT_MRT PS_MRT(VS_OUT input)
{
	PS_OUT_MRT output;

	float3 normal = normalize(input.Normal);
	normal = normal * 0.5 + 0.5; // from -1...1 to 0...1 range

	output.Normal = float4(normal, 1);
	output.Diffuse = float4(input.Color.rgb, 1);

	return output;
}

VS_DEBUG_OUT VS_DEBUG(VS_DEBUG_IN input)
{
	VS_DEBUG_OUT output;

	output.Pos = mul(View, input.Pos);
	output.Pos = mul(Projection, output.Pos);
	output.Color = input.Color;

	return output;
}

PS_DEBUG_OUT_MRT PS_DEBUG_MRT(VS_DEBUG_OUT input)
{
	PS_DEBUG_OUT_MRT output;
	output.Normal = 0;
	output.Diffuse = float4(input.Color.rgb, 1);
	return output;
}

technique10 GBufferCreate
{
	pass ShadowMap
	{
		SetVertexShader(CompileShader(vs_4_0, shadowGenVS()));
		SetGeometryShader(NULL);
		SetPixelShader(NULL);
	}

	pass GBufferGen
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS_MRT()));
	}

	pass DebugDraw
	{
		SetVertexShader(CompileShader(vs_4_0, VS_DEBUG()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS_DEBUG_MRT()));
	}
}
