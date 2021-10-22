#pragma once
#include "SharedComponent.h"
#include "InputLayout.h"
#include <string>
class VertexShader : public SharedComponent
{
public:
	VertexShader(Renderer& renderer, const std::wstring& path, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout);
	void Load(Renderer& renderer) override;
	static std::shared_ptr<VertexShader> GetOrCreate(Renderer& renderer, const std::wstring& path, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout);
private:
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	std::unique_ptr<InputLayout> inputLayout;
	static std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> cache;
};

