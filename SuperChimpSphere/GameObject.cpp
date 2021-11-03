#include "GameObject.h"
#include "Mesh.h"

GameObject::GameObject(Renderer& renderer)
{
	//components.push_back(Mesh::CreatePrimitiveSphere(renderer, 1.0F, 20U));
	components.push_back(std::make_unique<Mesh>(renderer, "Models/dog.obj"));
	transform *= DirectX::XMMatrixScaling(0.5F, 0.5F, 0.5F);
}

void GameObject::Update(Keyboard& keyboard, GameTime& time)
{
	for (auto& component : components)
	{
		component->Update(time);
	}
	auto input = keyboard.GetWASD() * (keyboard.GetKey(16 /*shift*/) ? 2.0F : 1.0F);
	transform *= DirectX::XMMatrixTranslation(-input.x * time.Delta(), (keyboard.GetKey('E') ? 1.0F : keyboard.GetKey('Q') ? -1.0F : 0.0F) * time.Delta(), input.y * time.Delta());
	transform *= DirectX::XMMatrixRotationY(keyboard.GetKey('R') ? time.Delta() : 0.0F);
}

void GameObject::Render(Renderer& renderer)
{
	renderer.SetModelMatrix(transform);
	for (auto& component : components)
	{
		component->Render(renderer);
	}
}
