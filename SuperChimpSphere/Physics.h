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
	void ResolveCollision(Collision& collision, float dt);
private:
	Transform& transform;
public:
	Vector3 velocity = Vector3s::zero;
	Vector3 surfaceNormal = Vector3s::up;
	bool touchingSurface = false;
	float drag = 0.5F;
	float mass = 1.0F;
	float bounciness = 1.0F;
	const float gravityMultiplier = 9.81F;
};

