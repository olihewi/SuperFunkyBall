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
}

void Physics::ResolveCollision(Collision& collision, float dt)
{
	Vector3 resultant = collision.normal * collision.penetration;
	float ms = 1.0F / dt;
	transform.position += resultant;
	//Vector3 bounceResult = (-velocity) * collision.normal; //(1+bounciness);
	//velocity += bounceResult;
	if (collision.penetration * ms < 12.0F)
		velocity += resultant * ms;
	touchingSurface = true;
	surfaceNormal = collision.normal;
}
