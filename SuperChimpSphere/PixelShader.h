#pragma once
#include "GraphicsComponent.h"
#include <string>
class PixelShader : public GraphicsComponent
{
public:
	PixelShader(Renderer& renderer, const std::wstring& path);
	void Load(Renderer& renderer) override;
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

