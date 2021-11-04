#pragma once
#include "GameObject.h"
class Camera : public GameObject
{
public:
	Camera(Renderer& renderer);
	void Update(Input& input, GameTime& time) override;
	void Render(Renderer& renderer) override;
};

