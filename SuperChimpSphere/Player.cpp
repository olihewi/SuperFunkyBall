#include "Player.h"
#include "Mesh.h"

Player::Player(Renderer& renderer)
{
	AddComponent(Mesh::CreatePrimitiveSphere(renderer, 0.5F, 16U));
	physics = dynamic_cast<Physics*>(AddComponent(std::make_unique<Physics>(transform)));
	collider = dynamic_cast<SphereCollider*>(AddComponent(std::make_unique<SphereCollider>(transform, 0.5F, physics)));
}

void Player::Update(Input& input, GameTime& time)
{
	GameObject::Update(input, time);
	auto movement = input.GetMovement() * time.Delta() * 4.0F;
	physics->velocity += Vector3(movement.x, 0.0F, -movement.y);
	if (input.GetPrimaryButtonDown())
	{
		physics->velocity.y += 5.0F;
	}
	//transform.rotation = DirectX::XMQuaternionRotationAxis({ physics->velocity.Normalized().x,physics->velocity.Normalized().y, physics->velocity.Normalized().z }, 1.0F);

	//transform *= DirectX::XMMatrixRotationY(keyboard.GetKey('R') ? time.Delta() : 0.0F);
}

void Player::Render(Renderer& renderer)
{
	transform.rotation *= DirectX::XMMatrixRotationX(physics->velocity.z * 0.025F) * DirectX::XMMatrixRotationZ(-physics->velocity.x * 0.025F);
	GameObject::Render(renderer);
}
