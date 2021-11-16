#pragma once
#include "MeshCollider.h"
class SphereCollider : public Collider
{
public:
	SphereCollider(Transform& _transform, float _radius, Physics* _physics = nullptr);
	float radius;
};

