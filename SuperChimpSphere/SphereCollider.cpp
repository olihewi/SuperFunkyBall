#include "SphereCollider.h"

SphereCollider::SphereCollider(Transform& transform, float _radius) : Collider(ColliderType::SPHERE, transform), radius(_radius)
{
}

bool SphereCollider::HasCollided(Collider& other)
{
	switch (other.colliderType)
	{
	case ColliderType::SPHERE:
		return VsSphere(dynamic_cast<SphereCollider&>(other));
	}
	return false;
}

bool SphereCollider::VsSphere(SphereCollider& other)
{
	return (transform.position - other.transform.position).Magnitude() <= radius + other.radius;
}
