#pragma once
#include "GameComponent.h"
#include "Transform.h"
#include "Vector3.h"
class Physics : public GameComponent
{
public:
	Physics(Transform& _transform);
	void Update(GameTime& time) override;
private:
	Transform& transform;
public:
	Vector3 velocity = Vector3s::zero;
	float drag = 2.0F;
	float mass = 1.0F;
	const float gravityMultiplier = 0.0F;// 9.81F;
};

