#pragma once
#include "GraphicsComponent.h"
class Sampler : public GraphicsComponent
{
public:
	Sampler(Renderer& renderer);
	void Load(Renderer& renderer) override;
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};

