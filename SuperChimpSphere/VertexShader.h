#pragma once
#include "GraphicsComponent.h"
#include <string>
class VertexShader : public GraphicsComponent
{
public:
	VertexShader(Renderer& renderer, const std::wstring& path);
	void Load(Renderer& renderer) override;
	ID3DBlob* GetBytecode();
private:
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
};

