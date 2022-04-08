struct Light
{
  float4 direction;
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
    float2 uv = input.tex;
    uv.x += light.direction.w / 50.0F;
    float4 t = tex.Sample(splr, uv);
    clip(t.a < 0.1F ? -1 : 1);
    return t;
  /*float4 t = float4(1,1,1,1);

  float3 viewDir = normalize(input.viewDir);
  float sunViewDot = dot(light.direction, viewDir);
  float sunZenithDot = light.direction.y;
  float viewZenithDot = input.viewDir.y;

  float sunViewDot01 = (sunViewDot + 1.0) * 0.5;
  float sunZenithDot01 = (sunZenithDot + 1.0) * 0.5;

  return float4(viewZenithDot, viewZenithDot, viewZenithDot, 1);*/

  /*
  // Base Sky Colour
  //float3 sunZenithColour = tex2D(_SunZenithGrad, float2(sunZenithDot01, 0.5)).rgb;
  float3 sunZenithColour = float3(0,0,sunZenithDot01);

  // Horizon Haze
  //float3 viewZenithColour = tex2D(_ViewZenithGrad, float2(sunZenithDot01, 0.5F)).rgb;
  float3 viewZenithColour = float3(sunZenithDot01, 0, 0);
  float viewZenithMask = pow(saturate(1.0 - viewZenithDot), 4);

  // Sun Bloom
  //float3 sunViewColour = tex2D(_SunViewGrad, float2(sunZenithDot01, 0.5F)).rgb;
  float3 sunViewColour = float3(sunZenithDot01, sunZenithDot01, sunZenithDot01);
  float sunViewMask = pow(saturate(sunViewDot), 10);

  // Final Sky Colour
  //float3 skyColour = sunZenithColour + (viewZenithMask * viewZenithColour) + (sunViewMask * sunViewColour);
  float3 skyColour = sunZenithColour + (viewZenithMask * viewZenithColour);

  //float4 t = tex.Sample(splr, input.tex);
  //clip(t.a < 0.1F ? -1 : 1);
  return float4(skyColour, 1);*/
}