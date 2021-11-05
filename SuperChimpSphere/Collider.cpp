#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(ColliderType _colliderType, Transform& _transform, Physics* _physics) : colliderType(_colliderType), transform(_transform), physics(_physics), index(CollisionManager::index++)
{
	CollisionManager::colliders.insert(std::make_pair(index, this));
}

Collider::~Collider()
{
	CollisionManager::colliders.erase(index);
}

void Collider::OnCollision(Collision collision)
{
	if (physics != nullptr)
	{
		physics->ResolveCollision(collision);
	}
}
