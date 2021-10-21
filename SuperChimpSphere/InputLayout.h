#pragma once
#include "GraphicsComponent.h"
class InputLayout : public GraphicsComponent
{
public:
	InputLayout(Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* vertexShaderBytecode);
	void Load(Renderer& renderer) override;
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

