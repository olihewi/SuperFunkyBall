#pragma once
#include "GraphicsComponent.h"
#include <string>
#include <unordered_map>
class PixelShader : public GraphicsComponent
{
public:
	PixelShader(Renderer& renderer, const std::wstring& path);
	void Load(Renderer& renderer) override;
	static std::shared_ptr<PixelShader> GetOrCreate(Renderer& renderer, const std::wstring& path);
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	static std::unordered_map<std::wstring,std::shared_ptr<PixelShader>> cache;
};

