#pragma once
#include "GameObject.h"
class Goal : public GameObject
{
public:
	Goal(Renderer& renderer, Vector3 _position, Vector3 rotation);
	Vector3 normal;
};

