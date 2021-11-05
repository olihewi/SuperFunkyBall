#pragma once
#include "GameComponent.h"
#include "Transform.h"
#include "Vector3.h"
#include "Collision.h"
class Physics : public GameComponent
{
public:
	Physics(Transform& _transform);
	void Update(GameTime& time) override;
	void ResolveCollision(Collision& collision);
private:
	Transform& transform;
public:
	Vector3 velocity = Vector3s::zero;
	float drag = 2.0F;
	float mass = 1.0F;
	const float gravityMultiplier = 9.81F;
};

