#pragma once
#include "GameObject.h"
class Camera : public GameObject
{
public:
	Camera(Renderer& renderer);
	void Update(Keyboard& keyboard, GameTime& time) override;
	void Render(Renderer& renderer) override;
};
