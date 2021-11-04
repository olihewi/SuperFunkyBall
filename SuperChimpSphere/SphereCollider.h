#pragma once
#include "Collider.h"
class SphereCollider : public Collider
{
public:
	SphereCollider(Transform& transform, float _radius);
	bool HasCollided(Collider& other);
private:
	bool VsSphere(SphereCollider& other);
	float radius;
};

