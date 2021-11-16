#pragma once
#include "GraphicsComponent.h"
#include <string>
#include <unordered_map>
#include "Colour.h"
#include "Vector3.h"
class Texture : public GraphicsComponent
{
public:
	Texture(Renderer& renderer, const std::string& path, unsigned int _slot);
	void Load(Renderer& renderer) override;
	static std::shared_ptr<Texture> GetOrCreate(Renderer& renderer, const std::string& path, unsigned int _slot = 0U);
	Vector2 GetDimensions();
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	unsigned int slot;
	static std::unordered_map<std::string, std::shared_ptr<Texture>> cache;
};

