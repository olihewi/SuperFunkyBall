#include "Transform.h"

Transform::Transform(Vector3 _position, DirectX::XMMATRIX _rotation, Vector3 _scale) : position(_position), rotation(_rotation), scale(_scale)
{
}

DirectX::XMMATRIX Transform::GetMatrix()
{
	DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();
	matrix *= DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	matrix = rotation * matrix;
	//matrix = DirectX::XMMatrixRotationQuaternion(rotation);
	//matrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) * matrix;
	matrix *= DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	return matrix;
}

void Transform::ApplyMatrix(Renderer& renderer)
{
	renderer.SetModelMatrix(GetMatrix());
}
