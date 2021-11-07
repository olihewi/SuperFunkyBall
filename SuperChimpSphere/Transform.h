#pragma once
#include "Renderer.h"
#include "Vector3.h"
class Transform
{
public:
	Transform() = default;
	Transform(Vector3 _position, DirectX::XMMATRIX _rotation, Vector3 _scale);

	DirectX::XMMATRIX GetMatrix();
	void ApplyMatrix(Renderer& renderer);
	Vector3 position = Vector3s::zero;
	DirectX::XMMATRIX rotation = DirectX::XMMatrixIdentity();
	Vector3 scale = Vector3s::one;
};

