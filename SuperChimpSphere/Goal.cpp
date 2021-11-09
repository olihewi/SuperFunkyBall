#include "Goal.h"
#include "Mesh.h"
#include "MeshCollider.h"

Goal::Goal(Renderer& renderer, Vector3 _position, Vector3 rotation)
{
	auto mesh = dynamic_cast<Mesh*>(AddComponent(std::make_unique<Mesh>(renderer, "Models/goal.obj", L"Models/goal.png")));
	//AddComponent(std::make_unique<MeshCollider>(transform, mesh));
	transform.position = _position;
	rotation *= DirectX::XM_PI / 180.0F;
	transform.rotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
}
