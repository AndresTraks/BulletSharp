cbuffer object
{
	matrix World;
	float4 Color;
}

cbuffer scene
{
	matrix View;
	matrix Projection;
	matrix ViewInverse;
}

struct VS_IN
{
	float4 Pos : POSITION;
	float3 Normal : NORMAL;
};

struct VS_OUT
{
    float4 Pos : SV_POSITION;
	float3 light : TEXCOORD0;
	float3 Normal : TEXCOORD1;
};

VS_OUT VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

	float3 Lamp0Pos = float3(20, 30, 10);

    output.Pos = mul(World, input.Pos);
	output.light = Lamp0Pos - output.Pos;
	output.Pos = mul(View, output.Pos);
    output.Pos = mul(Projection, output.Pos);

	output.Normal = mul(World, input.Normal);

    return output;
}

float4 PS( VS_OUT input ) : SV_Target
{
	float3 normal = normalize(input.Normal);
	float3 light = normalize(input.light);

	float shade = 0.5+0.5*pow(saturate(dot(light, normal)), 2.0);
	return float4(Color.rgb * shade, Color.a);
}

technique10 Render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
