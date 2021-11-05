#include "SphereCollider.h"

SphereCollider::SphereCollider(Transform& _transform, float _radius, Physics* _physics) : Collider(ColliderType::SPHERE, _transform, _physics), radius(_radius)
{
}

bool SphereCollider::SphereVsSphere(SphereCollider* a, SphereCollider* b)
{
	return (a->transform.position - b->transform.position).Magnitude() <= a->radius + b->radius;
}
bool SphereCollider::SphereVsMesh(SphereCollider* sphere, MeshCollider* mesh)
{
	Vector3 relativePos = mesh->transform.position - sphere->transform.position;
	for (unsigned int i = 0; i < mesh->mesh->triangles.size(); i += 3)
	{
		/// Separating Axis Test (https://realtimecollisiondetection.net/blog/?p=103)

		// Points of the triangle
		Vector3 A = mesh->mesh->vertices[mesh->mesh->triangles[i]] + relativePos;
		Vector3 B = mesh->mesh->vertices[mesh->mesh->triangles[i + 1]] + relativePos;
		Vector3 C = mesh->mesh->vertices[mesh->mesh->triangles[i + 2]] + relativePos;
		// Radius^2 is used to avoid the complexity of square root
		float r2 = sphere->radius * sphere->radius;
		// The normal of the triangle is the cross product of A->B and A->C
		Vector3 normal = (B - A).CrossProduct(C - A);
		float distFromPlane = A.DotProduct(normal);
		// If the sphere intersects with the triangle's plane
		if (distFromPlane * distFromPlane <= r2 * normal.SqrMagnitude())
		{
			// Dot products of each point of the triangle vs each other and self
			float aa = A.DotProduct(A);
			float ab = A.DotProduct(B);
			float ac = A.DotProduct(C);
			float bb = B.DotProduct(B);
			float bc = B.DotProduct(C);
			float cc = C.DotProduct(C);
			// If the sphere lies inside of any triangle vertex
			if ((aa <= r2) && (ab <= aa) && (ac <= aa) ||
				(bb <= r2) && (ab <= bb) && (bc <= bb) ||
				(cc <= r2) && (ac <= cc) && (bc <= cc))
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
				if ((Q1.DotProduct(Q1) <= r2 * e1 * e1 && Q1.DotProduct(QC) <= 0) ||
					(Q2.DotProduct(Q2) <= r2 * e2 * e2 && Q2.DotProduct(QA) <= 0) ||
					(Q3.DotProduct(Q3) <= r2 * e3 * e3 && Q3.DotProduct(QB) <= 0))
				{
					return true;
				}
			}
		}
	}
	return false;
}
