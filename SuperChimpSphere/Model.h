#pragma once
#include "GameObject.h"
class Model : public GameObject
{
public:
	Model(Renderer& renderer, std::string modelPath, std::wstring texturePath);
	void Update(Keyboard& keyboard, GameTime& time) override;
};

