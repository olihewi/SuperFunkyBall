#pragma once
#include <vector>
#include <memory>
#include "GameComponent.h"
#include <DirectXMath.h>
#include "Keyboard.h"
class GameObject
{
public:
	GameObject() = default;

	void AddComponent(std::unique_ptr<GameComponent> _component);

	virtual void Update(Keyboard& kb, GameTime& time);
	virtual void Render(Renderer& renderer);
protected:
	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity() * DirectX::XMMatrixTranslation(0.0F,0.0F,1.0F);
	std::vector<std::unique_ptr<GameComponent>> components;
};
