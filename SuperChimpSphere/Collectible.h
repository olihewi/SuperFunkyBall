#pragma once
#include "GameObject.h"
class Collectible : public GameObject
{
public:
	Collectible(Renderer& renderer, int _value, Vector3 position);
	void Update(Input& input, GameTime& time) override;
	void Render(Renderer& renderer) override;
	int value;
	float collectionTimer = -1.0F;
private:
	bool collected = false;
};

