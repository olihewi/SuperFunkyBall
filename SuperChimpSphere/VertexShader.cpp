#include "VertexShader.h"
#include <d3dcompiler.h>

std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> VertexShader::cache;

VertexShader::VertexShader(Renderer& renderer, const std::wstring& path, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout)
{
	D3DReadFileToBlob(path.c_str(), &blob);
	renderer.GetDevice()->CreateVertexShader(
		blob->GetBufferPointer(), // Shader bytecode
		blob->GetBufferSize(), // Bytecode size
		nullptr, // 
		&vertexShader // Vertex shader
	);
	inputLayout = std::make_unique<InputLayout>(renderer, layout, blob.Get());
}

void VertexShader::Load(Renderer& renderer)
{
	inputLayout->Load(renderer);
	renderer.GetContext()->VSSetShader(
		vertexShader.Get(), // Vertex Shader
		nullptr, // Class instances
		0U // Number of class instances
	);
}

std::shared_ptr<VertexShader> VertexShader::GetOrCreate(Renderer& renderer, const std::wstring& path, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout)
{
	cache.try_emplace(path, std::make_shared<VertexShader>(renderer, path, layout));
	return cache[path];
}
