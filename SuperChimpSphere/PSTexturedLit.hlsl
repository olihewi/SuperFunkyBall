struct Light
{
    float3 direction;
    //float worthless;
    float4 ambient;
    float4 diffuse;
};

cbuffer lightBuffer : register(b1)
{
    Light light;
};

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
    input.normal = normalize(input.normal);
    float4 diffuse = tex.Sample(splr, input.tex);
    float4 finalColour;
    finalColour = diffuse * light.ambient;
    finalColour += saturate(dot(light.direction, input.normal) * light.diffuse * diffuse);
    finalColour.a = diffuse.a;
    return finalColour;
}