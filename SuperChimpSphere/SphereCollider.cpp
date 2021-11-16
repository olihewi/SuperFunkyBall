#include "SphereCollider.h"

SphereCollider::SphereCollider(Transform& _transform, float _radius, Physics* _physics) : Collider(ColliderType::SPHERE, _transform, _physics), radius(_radius)
{
}
