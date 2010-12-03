cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	float4 Color;
}

struct VS_IN
{
	float3 Pos : POSITION;
};

struct VS_OUT
{
    float4 Pos : SV_POSITION;
};

VS_OUT VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    return output;
}

float4 PS( VS_OUT input ) : SV_Target
{
    return Color;
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
