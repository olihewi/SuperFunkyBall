#include "PhysicsTestSphere.h"
#include "Mesh.h"
#include "MeshCollider.h"
#include "SphereCollider.h"

PhysicsTestSphere::PhysicsTestSphere(Renderer& renderer, Vector3 position)
{
	transform.position = Vector3(0.0F,0.0F,0.0F);// = position;// +Vector3(0.0F, 2.0F, 0.0F);
	//Mesh* mesh = dynamic_cast<Mesh*>(AddComponent(Mesh::CreatePrimitiveSphere(renderer, 1.5F, 16U)));
	//AddComponent(std::make_unique<SphereCollider>(transform, 1.5F));
	//Mesh* mesh = dynamic_cast<Mesh*>(AddComponent(std::make_unique<Mesh>(renderer,"Models/dog.obj",L"Models/dog.png")));
	//Mesh* mesh = dynamic_cast<Mesh*>(AddComponent(Mesh::CreatePrimitiveCube(renderer,Vector3(1.5F,1.5F,1.5F))));
	Mesh* mesh = dynamic_cast<Mesh*>(AddComponent(std::make_unique<Mesh>(renderer, "Models/stage1.obj", L"Textures/UV_Checker.png")));
	AddComponent(std::make_unique<MeshCollider>(transform, mesh));
}
