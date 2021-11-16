#pragma once
#include "GameObject.h"
class Goal : public GameObject
{
public:
	Goal(Renderer& renderer, Vector3 _position, Vector3 rotation, std::string _nextLevel);
	Vector3 normal;
	std::string nextLevel;
};

