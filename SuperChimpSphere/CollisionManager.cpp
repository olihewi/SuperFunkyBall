#include "CollisionManager.h"
#include <algorithm>
#include <cmath>

std::map<unsigned int, Collider*> CollisionManager::colliders;
unsigned int CollisionManager::index = 0;

void CollisionManager::DetectCollisions()
{
	unsigned int x = 0;
	unsigned int y = 0;
	for (auto& i : colliders)
	{
		for (auto& j : colliders)
		{
			if (x++ > y)
			{
				DetectCollision(i.second, j.second);
			}
		}
		y++;
	}
}

bool CollisionManager::SphereVsSphere(Vector3 a, float aRadius, Vector3 b, float bRadius)
{
	return (a-b).Magnitude() <= aRadius + bRadius;
}

bool CollisionManager::SphereVsPlane(Vector3 sphere, float radius, Vector3 planePos, Vector3 planeNormal)
{
	float difference = (sphere - planePos).DotProduct(planeNormal);
	return (difference < radius);
}

void CollisionManager::DetectCollision(Collider* a, Collider* b)
{
	if (a->physics != nullptr)
	{
		a->physics->touchingSurface = false;
	}
	switch (a->colliderType)
	{
	case Collider::ColliderType::SPHERE:
		switch (b->colliderType)
		{
		case Collider::ColliderType::SPHERE:
			SphereVsSphere(dynamic_cast<SphereCollider*>(a), dynamic_cast<SphereCollider*>(b));
			break;
		case Collider::ColliderType::MESH:
			SphereVsMesh(dynamic_cast<SphereCollider*>(a), dynamic_cast<MeshCollider*>(b));
			break;
		}
		break;
	case Collider::ColliderType::MESH:
		switch (b->colliderType)
		{
		case Collider::ColliderType::SPHERE:
			SphereVsMesh(dynamic_cast<SphereCollider*>(b), dynamic_cast<MeshCollider*>(a));
			break;
		}
		break;
	}
}

void CollisionManager::SphereVsSphere(SphereCollider* a, SphereCollider* b)
{
	Vector3 difference = a->transform.position - b->transform.position;
	bool hit = difference.Magnitude() <= a->radius + b->radius;
	if (hit)
	{
		Vector3 normal = difference.Normalized();
		float depth = a->radius + b->radius - difference.Magnitude();
		a->OnCollision(Collision( hit, normal, depth ));
		b->OnCollision(Collision( hit, -normal, depth ));
	}
}
void CollisionManager::SphereVsMesh(SphereCollider* sphere, MeshCollider* mesh)
{
	std::vector<Collision> collisions;
	Vector3 relativePos = mesh->transform.position - sphere->transform.position;
	for (unsigned int i = 0; i < mesh->mesh->triangles.size(); i += 3)
	{
		// Points of the triangle
		Vector3 A = mesh->mesh->vertices[mesh->mesh->triangles[i]] + relativePos;
		Vector3 B = mesh->mesh->vertices[mesh->mesh->triangles[i + 2]] + relativePos;
		Vector3 C = mesh->mesh->vertices[mesh->mesh->triangles[i + 1]] + relativePos;
		Collision collision = SphereVsTriangle(sphere->radius, A, B, C, i);
		if (collision.hit)
		{
			collisions.push_back(collision);
			relativePos = mesh->transform.position - sphere->transform.position;
		}
	}
	if (static_cast<bool>(collisions.size()))
	{
		std::sort(collisions.begin(), collisions.end());
		sphere->OnCollision(collisions.front());
		while (collisions.size() > 1U)
		{
			collisions.erase(collisions.begin());
			auto& collision = collisions.front();
			Vector3 relativePos = mesh->transform.position - sphere->transform.position;
			Vector3 A = mesh->mesh->vertices[mesh->mesh->triangles[collision.index]] + relativePos;
			Vector3 B = mesh->mesh->vertices[mesh->mesh->triangles[collision.index + 2]] + relativePos;
			Vector3 C = mesh->mesh->vertices[mesh->mesh->triangles[collision.index + 1]] + relativePos;
			Collision test2 = SphereVsTriangle(sphere->radius, A, B, C, collision.index);
			if (test2.hit)
			{
				sphere->OnCollision(test2);
			}
		}
	}
}

Collision CollisionManager::SphereVsTriangle(float radius, Vector3& A, Vector3& B, Vector3& C, unsigned int index)
{
	/// Separating Axis Test (https://realtimecollisiondetection.net/blog/?p=103)
	float r2 = radius * radius;
	Vector3 normal = (B - A).CrossProduct(C - A);
	float distFromPlane = A.DotProduct(normal);
	// If the sphere intersects with the triangle's plane
	if (distFromPlane * distFromPlane < r2 * normal.SqrMagnitude())
	{
		// Dot products of each point of the triangle vs each other and self
		float aa = A.DotProduct(A);
		float ab = A.DotProduct(B);
		float ac = A.DotProduct(C);
		float bb = B.DotProduct(B);
		float bc = B.DotProduct(C);
		float cc = C.DotProduct(C);
		// If the sphere lies inside of each triangle vertex
		if (((aa < r2) || (ab < aa) || (ac < aa)) &&
			((bb < r2) || (ab < bb) || (bc < bb)) &&
			((cc < r2) || (ac < cc) || (bc < cc)))
		{
			// Differences between each point of the triangle
			Vector3 AB = B - A;
			Vector3 BC = C - B;
			Vector3 CA = A - C;
			// Distances between points of the triangls
			float d1 = ab - aa;
			float d2 = bc - bb;
			float d3 = ac - cc;
			float e1 = AB.DotProduct(AB);
			float e2 = BC.DotProduct(BC);
			float e3 = CA.DotProduct(CA);
			Vector3 Q1 = A * e1 - AB * d1;
			Vector3 Q2 = B * e2 - BC * d2;
			Vector3 Q3 = C * e3 - CA * d3;
			Vector3 QC = C * e1 - Q1;
			Vector3 QA = A * e2 - Q2;
			Vector3 QB = B * e3 - Q3;
			// If the sphere is inside of a triangle edge
			if ((Q1.DotProduct(Q1) < r2 * e1 * e1 || Q1.DotProduct(QC) < 0) &&
				(Q2.DotProduct(Q2) < r2 * e2 * e2 || Q2.DotProduct(QA) < 0) &&
				(Q3.DotProduct(Q3) < r2 * e3 * e3 || Q3.DotProduct(QB) < 0))
			{
				return Collision(true, normal.Normalized(), distFromPlane + radius * normal.Magnitude(), index);
			}
		}
	}
	return Collision(false,Vector3s::zero,0.0F);
}
