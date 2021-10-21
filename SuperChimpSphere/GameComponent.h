#pragma once
#include "GameTime.h"
#include "Renderer.h"
class GameComponent
{
public:
	virtual void Update(GameTime& time) {};
	virtual void Render(Renderer& renderer) {};
};

