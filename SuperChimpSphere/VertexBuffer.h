#pragma once
#include "GraphicsComponent.h"
#include "Vector3.h"
class VertexBuffer : public GraphicsComponent
{
public:
	VertexBuffer(Renderer& renderer, const std::vector<Vector3>& vertices);
	void Load(Renderer& renderer) override;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	unsigned int stride;
};

