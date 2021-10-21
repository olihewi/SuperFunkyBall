#include "PixelShader.h"
#include <d3dcompiler.h>

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
