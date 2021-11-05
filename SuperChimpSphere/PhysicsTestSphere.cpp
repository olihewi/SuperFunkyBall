#include "PhysicsTestSphere.h"
#include "Mesh.h"
#include "MeshCollider.h"

PhysicsTestSphere::PhysicsTestSphere(Renderer& renderer, Vector3 position)
{
	transform.position = position;
	//Mesh* mesh = dynamic_cast<Mesh*>(AddComponent(Mesh::CreatePrimitiveSphere(renderer, 0.5F, 16U
	Mesh* mesh = dynamic_cast<Mesh*>(AddComponent(std::make_unique<Mesh>(renderer,"Models/dog.obj",L"Models/dog.png")));
	AddComponent(std::make_unique<MeshCollider>(transform, mesh));
}
