#pragma once
#include "Renderer.h"
class GraphicsComponent
{
public:
	virtual void Load(Renderer& renderer) = 0;
	virtual ~GraphicsComponent() = default;
};

