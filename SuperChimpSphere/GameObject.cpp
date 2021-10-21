#include "GameObject.h"
#include "Mesh.h"

GameObject::GameObject(Renderer& renderer)
{
	components.push_back(std::make_unique<Mesh>(Mesh::CreatePrimitiveSphere(renderer, 1.0F, 20U)));
}

void GameObject::Update(Keyboard& keyboard, GameTime& time)
{
	for (auto& component : components)
	{
		component->Update(time);
	}
	Vector3 input
	{
		keyboard.GetKey('D') ? -1.0F : keyboard.GetKey('A') ? 1.0F : 0.0F,
		0.0F,
		keyboard.GetKey('S') ? -1.0F : keyboard.GetKey('W') ? 1.0F : 0.0F
	};
	transform *= DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(input.x * time.Delta(), 0.0F, input.z * time.Delta()));
}

void GameObject::Render(Renderer& renderer)
{
	renderer.SetModelMatrix(transform);
	for (auto& component : components)
	{
		component->Render(renderer);
	}
}
