#pragma once
#include "GraphicsComponent.h"
class TriangleBuffer : public GraphicsComponent
{
public:
	TriangleBuffer(Renderer& renderer, const std::vector<unsigned int>& triangles);
	void Load(Renderer& renderer) override;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
};

