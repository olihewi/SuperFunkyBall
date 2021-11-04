#include "Model.h"
#include "Mesh.h"

Model::Model(Renderer& renderer, std::string modelPath, std::wstring texturePath)
{
	AddComponent(std::make_unique<Mesh>(renderer, modelPath, texturePath));
	transform *= DirectX::XMMatrixScaling(0.5F, 0.5F, 0.5F);
}

void Model::Update(Keyboard& keyboard, GameTime& time)
{
	GameObject::Update(keyboard, time);
	auto input = keyboard.GetWASD() * (keyboard.GetKey(16 /*shift*/) ? 2.0F : 1.0F);
	transform *= DirectX::XMMatrixTranslation(-input.x * time.Delta(), (keyboard.GetKey('E') ? 1.0F : keyboard.GetKey('Q') ? -1.0F : 0.0F) * time.Delta(), input.y * time.Delta());
	transform *= DirectX::XMMatrixRotationY(keyboard.GetKey('R') ? time.Delta() : 0.0F);
}
