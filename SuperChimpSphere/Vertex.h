#pragma once
#include "Vector3.h"
struct Vertex
{
public:
	Vertex(const Vector3& _pos, const Vector2& _uv, const Vector3& _normal) : pos(_pos), uv(_uv), normal(_normal)
	{
	}
	Vector3 pos;
	Vector2 uv;
	Vector3 normal;
};