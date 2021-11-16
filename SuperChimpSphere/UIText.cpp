#include "UIText.h"

UIText::UIText(Renderer& renderer, std::string _text, Vector2 position) : text(_text)
{
	float sep = 0.0F;
	for (auto& c : characters)
	{
		c = std::make_unique<UIImage>(renderer, "Textures/Font.png", Vector2(0.1F, 0.1F), position + Vector2s::right * sep);
		sep += 0.05F;
	}
}

void UIText::Render(Renderer& renderer)
{
	size_t i = 0;
	size_t max = characters.size();
	for (char c : text)
	{
		if (i >= max) { return; }
		auto& s = characters[i];
		int index = static_cast<int>(c) - 32;
		s->uvUL = Vector2(index % 15 / 15.0F, (index / 15) / 8.0F);
		//s->uvUL = Vector2(1/15.0F, 0);
		s->uvBR = s->uvUL + Vector2(1.0F / 15.0F, 1.0F / 8.0F);
		s->Render(renderer);
		i++;
	}
}
