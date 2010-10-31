
struct MapVertexToPixel
{
    float4 position : POSITION;
    float3 position2 : TEXCOORD0;
};

float4x4 World : WORLD;
float4x4 ViewProjection : VIEWPROJECTION;

MapVertexToPixel RenderVS(float4 Position : POSITION)
{
    MapVertexToPixel Out;
	Out.position = mul(Position, mul(World, ViewProjection));
	Out.position2 = mul(Position, World);
    return Out;
}

float xor(float a, float b)
{
	if (a == b)
		return 0;
	return 1;
}

float4 RenderPS(MapVertexToPixel In) : COLOR
{
	float3 pos = floor(frac(In.position2 / 10) * 2);
	float cl = 1 - 0.05 * xor(xor(pos.x, pos.y), pos.z);
	return float4(cl,cl,cl,1);
}

technique Main
{
    pass RenderShadowMap
    {
        VertexShader = compile vs_2_0 RenderVS();
        PixelShader = compile ps_2_0 RenderPS();
    }
}
