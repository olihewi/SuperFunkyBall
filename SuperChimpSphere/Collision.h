#pragma once
#include "Vector3.h"

struct Collision
{
	Collision(bool _hit, Vector3 _normal) : hit(_hit), normal(_normal)
	{

	}
	bool hit = false;
	Vector3 normal;
};