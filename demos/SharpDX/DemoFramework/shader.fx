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
	float3 Pos2 : TEXCOORD2;
};

VS_OUT VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.Pos = mul(World, input.Pos);
	output.Pos2 = output.Pos;
    output.Pos = mul(View, output.Pos);
    output.Pos = mul(Projection, output.Pos);

	output.Normal = mul(WorldInverseTranspose, input.Normal).xyz;

    return output;
}

float4 PS( VS_OUT input ) : SV_Target
{
	float3 Lamp0Pos = float3(20, 30, 20);
	float3 light = normalize(Lamp0Pos - input.Pos2);

	float shade = 0.5+0.5*saturate(dot(light, input.Normal));
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
