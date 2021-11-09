#pragma once
#include "GameComponent.h"
#include "Vector3.h"
#include "Colour.h"
class Light : public GameComponent
{
public:
	Light(Renderer& renderer, Vector3 _direction, Colour _ambient, Colour _diffuse);
	void Render(Renderer& renderer) override;
private:
	Vector3 direction;
	Colour ambient, diffuse;
};

