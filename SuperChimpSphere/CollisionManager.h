#pragma once
#include "SphereCollider.h"
#include "MeshCollider.h"
#include <map>
class CollisionManager
{
public:
	static void DetectCollisions(float dt);
	static std::map<unsigned int, Collider*> colliders;
	static bool SphereVsSphere(Vector3 a, float aRadius, Vector3 b, float bRadius);
	static bool SphereVsPlane(Vector3 sphere, float radius, Vector3 planePos, Vector3 planeNormal);
	static unsigned int index;
private:
	static void DetectCollision(Collider* a, Collider* b, float dt);
	static void SphereVsSphere(SphereCollider* a, SphereCollider* b, float dt);
	static void SphereVsMesh(SphereCollider* sphere, MeshCollider* mesh, float dt);
	static Collision SphereVsTriangle(float radius, Vector3& A, Vector3& B, Vector3& C, unsigned int index = 0);
};

