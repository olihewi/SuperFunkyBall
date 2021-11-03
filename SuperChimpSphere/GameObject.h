#pragma once
#include <vector>
#include <memory>
#include "GameComponent.h"
#include <DirectXMath.h>
#include "Keyboard.h"
class GameObject
{
public:
	GameObject(Renderer& renderer);
	void Update(Keyboard& kb, GameTime& time);
	void Render(Renderer& renderer);
private:
	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity() * DirectX::XMMatrixTranslation(0.0F,0.0F,1.0F);
	std::vector<std::unique_ptr<GameComponent>> components;
};
