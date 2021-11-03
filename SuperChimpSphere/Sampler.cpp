#include "Sampler.h"

Sampler::Sampler(Renderer& renderer)
{
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	renderer.GetDevice()->CreateSamplerState(&samplerDesc, &sampler);
}

void Sampler::Load(Renderer& renderer)
{
	renderer.GetContext()->PSSetSamplers(0U, 1U, sampler.GetAddressOf());
}
