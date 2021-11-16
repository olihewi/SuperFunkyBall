struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

Texture2D tex;
SamplerState splr;

float4 main(PixelShaderInput input) : SV_TARGET
{
    // Draw the entire triangle yellow.
    float4 t = tex.Sample(splr, input.tex);
    clip(t.a < 0.1F ? -1 : 1);
    return t;
}