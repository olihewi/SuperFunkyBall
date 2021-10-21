#include "InputLayout.h"

InputLayout::InputLayout(Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* vertexShaderBytecode)
{
	renderer.GetDevice()->CreateInputLayout(
		layout.data(), // Layout to use
		static_cast<unsigned int>(layout.size()), // Number of elements
		vertexShaderBytecode->GetBufferPointer(), // Vertex shader bytecode
		vertexShaderBytecode->GetBufferSize(), // Size of the vertex shader bytecode
		&inputLayout
	);
}

void InputLayout::Load(Renderer& renderer)
{
	renderer.GetContext()->IASetInputLayout(
		inputLayout.Get() // Input layout
	);
}
