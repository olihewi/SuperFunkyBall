#include "Physics.h"

Physics::Physics(Transform& _transform) : transform(_transform)
{
}

void Physics::Update(GameTime& time)
{
	float delta = time.Delta();
	velocity.y -= gravityMultiplier * delta;
	velocity = velocity / (1 + drag * delta);
	Vector3 v = velocity * delta;
	transform.position += v;
	if (transform.position.y < -1.0F)
	{
		velocity.y = 5.0F;
	}
}
