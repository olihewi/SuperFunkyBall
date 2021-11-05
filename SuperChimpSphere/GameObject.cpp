#include "GameObject.h"
#include "Mesh.h"

GameComponent* GameObject::AddComponent(std::unique_ptr<GameComponent> _component)
{
	components.push_back(std::move(_component));
	return components.back().get();
}

void GameObject::Update(Input& input, GameTime& time)
{
	for (auto& component : components)
	{
		component->Update(time);
	}
}

void GameObject::Render(Renderer& renderer)
{
	transform.ApplyMatrix(renderer);
	for (auto& component : components)
	{
		component->Render(renderer);
	}
}
