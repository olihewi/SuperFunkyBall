#include "Player.h"
#include "Mesh.h"

Player::Player(Renderer& renderer)
{
	transform.position.y = 2.0F;
	physics = dynamic_cast<Physics*>(AddComponent(std::make_unique<Physics>(transform)));
	collider = dynamic_cast<SphereCollider*>(AddComponent(std::make_unique<SphereCollider>(transform, 0.5F, physics)));
	AddComponent(std::make_unique<Mesh>(renderer, "Models/ball.obj", "Textures/ball.png"));
	//AddComponent(Mesh::CreatePrimitiveSphere(renderer, 0.5F, 16U, "Textures/Ball.png"));
}

void Player::Update(Input& input, GameTime& time)
{
	Vector2 relativeMovement = input.GetMovement();

	cameraTilt = cameraTilt.Lerp(relativeMovement * time.Delta() * 3.0F, 0.2F);
	relativeMovement.y = -relativeMovement.y;
	relativeMovement = relativeMovement.Rotate(cameraDir.x);

	acceleration = acceleration.Lerp(relativeMovement * time.Delta() * 3.0F,0.2F);
	physics->velocity += Vector3(acceleration.x, 0.0F, acceleration.y);

	/*if (input.GetPrimaryButtonDown() && physics->touchingSurface)
	{
		physics->velocity += (Vector3s::up + physics->surfaceNormal) * 2.5F;
	}*/

	Vector2 vel2D{ physics->velocity.x,physics->velocity.z };
	cameraDir += input.GetCamera() * time.Delta() * 1.0F / (1.0F + vel2D.Magnitude() * 0.1F) * 2.0F;
	cameraDir.y = std::fmaxf(std::fminf(cameraDir.y,0.75F), 0.0F);

	GameObject::Update(input, time);
}

void Player::Render(Renderer& renderer)
{
	transform.rotation *= DirectX::XMMatrixRotationX(physics->velocity.z * 0.025F) * DirectX::XMMatrixRotationZ(-physics->velocity.x * 0.025F);
	GameObject::Render(renderer);
}
