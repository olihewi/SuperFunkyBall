struct VSOut
{
	float3 colour : Colour;
	float4 pos : SV_Position;
};

cbuffer CBuf
{
	matrix transform;
};

VSOut main( float3 pos : Position, float3 colour : Colour )
{
	VSOut vso;
	vso.pos = mul(float4(pos.x, pos.y, pos.z, 1.0F), transform);
	vso.colour = colour;
	return vso;
}