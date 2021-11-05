#pragma once
#include "GameComponent.h"
#include "Physics.h"
class Collider: public GameComponent
{
public:
	enum class ColliderType
	{
		NONE,
		SPHERE,
		MESH
	};
	Collider(ColliderType _colliderType, Transform& _transform, Physics* _physics);
	~Collider();
	void OnCollision(Collision collision);
	Transform& transform;
	ColliderType colliderType;
	Physics* physics;
	unsigned int index;
};

