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
	/*if (transform.position.y <= 0.0F && velocity.y < 0.0F)
	{
		transform.position.y = 0.0F;
		velocity.y = 0.0F;
	}*/
}

void Physics::ResolveCollision(Collision& collision)
{
	Vector3 resultant = collision.normal * collision.penetration;
	transform.position += resultant;
	velocity += resultant * 60.0F;
	touchingSurface = true;
	surfaceNormal = collision.normal;
}
