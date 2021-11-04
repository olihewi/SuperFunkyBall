#pragma once
#include <vector>
#include <memory>
#include "GameComponent.h"
#include <DirectXMath.h>
#include "Keyboard.h"
#include "Transform.h"
class GameObject
{
public:
	GameObject() = default;

	void AddComponent(std::unique_ptr<GameComponent> _component);

	virtual void Update(Keyboard& kb, GameTime& time);
	virtual void Render(Renderer& renderer);
protected:
	Transform transform;
	std::vector<std::unique_ptr<GameComponent>> components;
};
