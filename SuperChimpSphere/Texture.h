#pragma once
#include "GraphicsComponent.h"
#include <string>
#include <unordered_map>
#include "Colour.h"
class Texture : public GraphicsComponent
{
public:
	Texture(Renderer& renderer, const std::wstring& path, unsigned int _slot);
	void Load(Renderer& renderer) override;
	static std::shared_ptr<Texture> GetOrCreate(Renderer& renderer, const std::wstring& path, unsigned int _slot = 0U);
private:
	std::unique_ptr<Colour[]> pixels;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	unsigned int slot;
	static std::unordered_map<std::wstring, std::shared_ptr<Texture>> cache;
};

