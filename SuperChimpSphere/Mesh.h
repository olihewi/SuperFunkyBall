#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include <vector>
class Mesh
{
public:
	std::vector<Vector3> vertices;
	std::vector<int> triangles;
	std::vector<Vector2> uvs;
};

