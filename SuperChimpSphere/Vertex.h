#pragma once
#include "Vector3.h"
struct Vertex
{
public:
	Vertex(const Vector3& _pos, const Vector2& _uv) : pos(_pos), uv(_uv)
	{
	}
	Vector3 pos;
	Vector2 uv;
};