cbuffer object
{
	matrix World;
	matrix WorldInverseTranspose;
	float4 Color;
}

cbuffer scene
{
	matrix View;
	matrix Projection;
}

struct VS_IN
{
	float4 Pos : POSITION;
	float3 Normal : NORMAL;
};

struct VS_OUT
{
    float4 Pos : SV_POSITION;
	float3 Normal : TEXCOORD0;
	float3 lightVec : TEXCOORD1;
};

VS_OUT VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.Pos = mul(World, input.Pos);
    output.Pos = mul(View, output.Pos);
    output.Pos = mul(Projection, output.Pos);

	output.Normal = mul(WorldInverseTranspose, input.Normal).xyz;

	float3 Lamp0Pos = float3(20, 50, 20);
	float4 Po = float4(input.Pos.xyz,1);
	float3 Pw = mul(World, Po).xyz;
	output.lightVec = normalize(Lamp0Pos - Pw);

    return output;
}

float4 PS( VS_OUT input ) : SV_Target
{
	float shade = 0.7+0.3*saturate(dot(input.lightVec, input.Normal));
	float4 color = Color;
	color.rgb *= shade;
    return color;
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
