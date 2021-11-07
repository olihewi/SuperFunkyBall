#pragma once
#include "Vector3.h"

struct Collision
{
	Collision(bool _hit, Vector3 _normal, float _penetration) : hit(_hit), normal(_normal), penetration(_penetration)
	{

	}
	bool operator<(const Collision& c) const
	{
		return penetration < c.penetration;
	}

	bool hit = false;
	Vector3 normal;
	float penetration;
};