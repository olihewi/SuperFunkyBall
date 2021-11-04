#pragma once
#include "GameComponent.h"
#include "Transform.h"
class Collider: public GameComponent
{
public:
	enum class ColliderType
	{
		NONE,
		SPHERE
	};
	Collider(ColliderType _colliderType, Transform& _transform) : colliderType(_colliderType), transform(_transform) {}
	virtual bool HasCollided(Collider& other) { return true; }
	Transform& transform;
	ColliderType colliderType;
};

