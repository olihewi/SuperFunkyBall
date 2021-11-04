#pragma once
#include "GameObject.h"
#include "Physics.h"
class Player : public GameObject
{
public:
	Player(Renderer& renderer);
	void Update(Input& input, GameTime& time) override;
private:
	Physics* physics;
};

