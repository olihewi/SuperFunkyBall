#pragma once
#include "MeshCollider.h"
class SphereCollider : public Collider
{
public:
	SphereCollider(Transform& _transform, float _radius, Physics* _physics = nullptr);
	static bool SphereVsSphere(SphereCollider* a, SphereCollider* b);
	static bool SphereVsMesh(SphereCollider* sphere, MeshCollider* mesh);
	float radius;
};

