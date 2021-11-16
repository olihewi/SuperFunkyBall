struct VertexShaderInput
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL;
};

Texture2D tex;

PixelShaderInput main( VertexShaderInput input )
{
    PixelShaderInput output;
    output.pos = float4(input.pos.x, input.pos.y, 0.0F, 1.0F);
    output.tex = input.tex;
    output.normal = input.normal;
	return output;
}