struct Light
{
    float3 direction;
    float4 ambient;
    float4 diffuse;
};

cbuffer lightBuffer : register(b1)
{
    Light light;
}

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL;
};

Texture2D tex;
SamplerState splr;

float4 main(PixelShaderInput input) : SV_TARGET
{
    // Draw the entire triangle yellow.
    return tex.Sample(splr, input.tex);
}