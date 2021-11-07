#pragma once
#include "SphereCollider.h"
#include "MeshCollider.h"
#include <map>
class CollisionManager
{
public:
	static void DetectCollisions();
	static std::map<unsigned int, Collider*> colliders;
	static unsigned int index;
private:
	static void DetectCollision(Collider* a, Collider* b);
	static void SphereVsSphere(SphereCollider* a, SphereCollider* b);
	static void SphereVsMesh(SphereCollider* sphere, MeshCollider* mesh);
	static Collision SphereVsTriangle(float radius, Vector3& A, Vector3& B, Vector3& C);
};

