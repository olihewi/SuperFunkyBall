#include "Texture.h"
#include "WICTextureLoader.h"
#include <fstream>

std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::cache;

Texture::Texture(Renderer& renderer, const std::string& path, unsigned int _slot) : slot(_slot)
{
	const char* str = path.c_str();
	wchar_t* wstr = new wchar_t[strlen(str) + 1];
	mbstowcs_s(NULL, wstr, strlen(str) + 1, str, strlen(str));
	
	DirectX::CreateWICTextureFromFile(renderer.GetDevice(), wstr, NULL, &shaderResourceView);
}

void Texture::Load(Renderer& renderer)
{
	renderer.GetContext()->PSSetShaderResources(
		slot,
		1U,
		shaderResourceView.GetAddressOf()
	);
}

std::shared_ptr<Texture> Texture::GetOrCreate(Renderer& renderer, const std::string& path, unsigned int _slot)
{
	cache.try_emplace(path, std::make_shared<Texture>(renderer, path, _slot));
	return cache[path];
}
