#pragma once
#include "Renderer.h"
#include "Vector3.h"
class Transform
{
public:
	Transform() = default;
	Transform(Vector3 _position, Vector3 _rotation, Vector3 _scale);

	DirectX::XMMATRIX GetMatrix();
	void ApplyMatrix(Renderer& renderer);
	Vector3 position = Vector3s::zero;
	Vector3 rotation = Vector3s::zero;
	Vector3 scale = Vector3s::one;
};

