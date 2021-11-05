#pragma once
#include "Mesh.h"
#include "Collider.h"
class MeshCollider : public Collider
{
public:
	MeshCollider(Transform& _transform, Mesh* _mesh, Physics* _physics = nullptr);
	Mesh* mesh;
};

