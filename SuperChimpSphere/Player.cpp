#include "Player.h"
#include "Mesh.h"

Player::Player(Renderer& renderer)
{
	transform.position.y = 1.0F;
	physics = dynamic_cast<Physics*>(AddComponent(std::make_unique<Physics>(transform)));
	collider = dynamic_cast<SphereCollider*>(AddComponent(std::make_unique<SphereCollider>(transform, 0.5F, physics)));
	AddComponent(Mesh::CreatePrimitiveSphere(renderer, 0.5F, 16U));
}

void Player::Update(Input& input, GameTime& time)
{
	acceleration = acceleration.Lerp(input.GetMovement() * time.Delta() * 4.0F,0.25F);
	physics->velocity += Vector3(acceleration.x, 0.0F, -acceleration.y);
	if (input.GetPrimaryButtonDown() && physics->touchingSurface)
	{
		physics->velocity += (Vector3s::up + physics->surfaceNormal) * 2.5F;
	}
	if (transform.position.y < -10.0F)
	{
		transform.position = Vector3s::up;
	}
	GameObject::Update(input, time);
	//transform.rotation = DirectX::XMQuaternionRotationAxis({ physics->velocity.Normalized().x,physics->velocity.Normalized().y, physics->velocity.Normalized().z }, 1.0F);

	//transform *= DirectX::XMMatrixRotationY(keyboard.GetKey('R') ? time.Delta() : 0.0F);
}

void Player::Render(Renderer& renderer)
{
	//Vector3 rotationAxis = physics->velocity.Normalized().CrossProduct(physics->surfaceNormal);
	//transform.rotation *= DirectX::XMMatrixRotationAxis(DirectX::XMVectorSet(rotationAxis.x, rotationAxis.y, rotationAxis.z, 1.0F), physics->velocity.Magnitude());
	transform.rotation *= DirectX::XMMatrixRotationX(physics->velocity.z * 0.025F) * DirectX::XMMatrixRotationZ(-physics->velocity.x * 0.025F);
	GameObject::Render(renderer);
}
