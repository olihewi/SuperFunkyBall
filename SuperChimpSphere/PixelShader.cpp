#include "PixelShader.h"
#include <d3dcompiler.h>

std::unordered_map<std::wstring,std::shared_ptr<PixelShader>> PixelShader::cache;

PixelShader::PixelShader(Renderer& renderer, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	D3DReadFileToBlob(path.c_str(), &blob);
	renderer.GetDevice()->CreatePixelShader(
		blob->GetBufferPointer(), // Bytecode
		blob->GetBufferSize(), // Bytecode size
		nullptr, // Class Linkage
		&pixelShader // Pixel Shader
	);
}

void PixelShader::Load(Renderer& renderer)
{
	renderer.GetContext()->PSSetShader(
		pixelShader.Get(), // Pixel shader to load
		nullptr, // Class instances
		0U // Number of class instances
	);
}

std::shared_ptr<PixelShader> PixelShader::GetOrCreate(Renderer& renderer, const std::wstring& path)
{
	cache.try_emplace(path, std::make_shared<PixelShader>(renderer, path));
	return cache[path];
}
