#pragma once
#include <vector>
#include <memory>
#include "GameComponent.h"
#include "Input.h"
#include "Transform.h"
class GameObject
{
public:
	GameObject() = default;

	GameComponent* AddComponent(std::unique_ptr<GameComponent> _component);

	virtual void Update(Input& input, GameTime& time);
	virtual void Render(Renderer& renderer);
	Transform transform;
protected:
	std::vector<std::unique_ptr<GameComponent>> components;
};
