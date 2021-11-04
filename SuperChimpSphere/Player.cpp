#include "Player.h"
#include "Mesh.h"
#include "Physics.h"

Player::Player(Renderer& renderer)
{
	AddComponent(Mesh::CreatePrimitiveSphere(renderer, 0.5F, 20U));
	AddComponent(std::make_unique<Physics>(transform));
	physics = dynamic_cast<Physics*>(components.back().get());
}

void Player::Update(Input& input, GameTime& time)
{
	GameObject::Update(input, time);
	auto movement = input.GetMovement() * time.Delta() * 4.0F;
	movement.x *= -1.0F;
	physics->velocity += Vector3(movement.x, 0.0F, movement.y);
	//transform.rotation = DirectX::XMQuaternionRotationAxis({ physics->velocity.Normalized().x,physics->velocity.Normalized().y, physics->velocity.Normalized().z }, 1.0F);
	transform.rotation.z -= physics->velocity.x * 0.025F;
	transform.rotation.x += physics->velocity.z * 0.025F;

	//transform *= DirectX::XMMatrixRotationY(keyboard.GetKey('R') ? time.Delta() : 0.0F);
}
