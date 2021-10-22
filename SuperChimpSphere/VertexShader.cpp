#include "VertexShader.h"
#include <d3dcompiler.h>

std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> VertexShader::cache;
VertexShader::VertexShader(Renderer& renderer, const std::wstring& path)
{
	D3DReadFileToBlob(path.c_str(), &blob);
	renderer.GetDevice()->CreateVertexShader(
		blob->GetBufferPointer(), // Shader bytecode
		blob->GetBufferSize(), // Bytecode size
		nullptr, // 
		&vertexShader // Vertex shader
	);
}

void VertexShader::Load(Renderer& renderer)
{
	renderer.GetContext()->VSSetShader(
		vertexShader.Get(), // Vertex Shader
		nullptr, // Class instances
		0U // Number of class instances
	);
}

ID3DBlob* VertexShader::GetBytecode()
{
	return blob.Get();
}

std::shared_ptr<VertexShader> VertexShader::GetOrCreate(Renderer& renderer, const std::wstring& path)
{
	cache.try_emplace(path, std::make_shared<VertexShader>(renderer, path));
	return cache[path];
}
