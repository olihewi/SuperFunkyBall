cbuffer simpleConstantBuffer : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
};

struct VertexShaderInput
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD1;
    float3 normal : NORMAL;
};

PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput vertexShaderOutput;
    float4 pos = float4(input.pos, 1.0f);

    // Transform the vertex position into projection space.
    pos = mul(pos, model);
    pos = mul(pos, view);
    pos = mul(pos, projection);
    vertexShaderOutput.pos = pos;
    vertexShaderOutput.tex = input.tex;
    vertexShaderOutput.normal = mul(input.normal,model);

    return vertexShaderOutput;
}