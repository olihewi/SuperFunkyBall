#pragma once
#include "GameObject.h"
#include "UIImage.h"
class UIText : public GameObject
{
public:
	UIText(Renderer& renderer, std::string _text);
	void Render(Renderer& renderer) override;
	std::array<std::unique_ptr<UIImage>, 16> characters;
	std::string text;
};

