#pragma once
#include "SharedComponent.h"
#include <string>
class VertexShader : public SharedComponent
{
public:
	VertexShader(Renderer& renderer, const std::wstring& path);
	void Load(Renderer& renderer) override;
	ID3DBlob* GetBytecode();
	static std::shared_ptr<VertexShader> GetOrCreate(Renderer& renderer, const std::wstring& path);
private:
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	static std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> cache;
};

