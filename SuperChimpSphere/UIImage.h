#pragma once
#include "GameComponent.h"
#include <string>
#include "Vector3.h"
#include "GraphicsComponent.h"
class UIImage : public GameComponent
{
public:
	UIImage(Renderer& renderer, std::string imagePath, Vector2 _dimensions, Vector2 _position = Vector2s::zero);
	void Render(Renderer& renderer) override;
	Vector2 position, dimensions;
	Vector2 uvUL = Vector2s::zero;
	Vector2 uvBR = Vector2s::one;
protected:
	std::vector<std::shared_ptr<GraphicsComponent>> components;
private:
	const std::vector<D3D11_INPUT_ELEMENT_DESC> elementDesc
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
};

