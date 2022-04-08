#include "Player.h"
#include "Mesh.h"

Player::Player(Renderer& renderer)
{
	transform.position.y = 2.0F;
	physics = dynamic_cast<Physics*>(AddComponent(std::make_unique<Physics>(transform)));
	collider = dynamic_cast<SphereCollider*>(AddComponent(std::make_unique<SphereCollider>(transform, 0.5F, physics)));
	AddComponent(std::make_unique<Mesh>(renderer, "Models/newball.obj", "Textures/NewBall.png"));
	//AddComponent(Mesh::CreatePrimitiveSphere(renderer, 0.5F, 16U, "Textures/Ball.png"));
}

void Player::Update(Input& input, GameTime& time)
{
	Vector2 relativeMovement = input.GetMovement();

	cameraTilt = cameraTilt.Lerp(relativeMovement / 16.0F, time.Delta() * 10.0F);
	relativeMovement.y = -relativeMovement.y;
	relativeMovement = relativeMovement.Rotate(cameraDir.x);

	acceleration = acceleration.Lerp(relativeMovement * 4.0F,time.Delta() * 10.0F);
	physics->velocity += Vector3(acceleration.x, 0.0F, acceleration.y) * time.Delta();

	Vector2 vel2D{ physics->velocity.x,physics->velocity.z };
	cameraDir += input.GetCamera() * time.Delta() * 1.0F / (1.0F + vel2D.Magnitude() * 0.1F) * 2.0F;
	cameraDir.y = std::fmaxf(std::fminf(cameraDir.y,0.9F), 0.0F);

	transform.rotation *= DirectX::XMMatrixRotationX(physics->velocity.z * 0.5F * 3.14F * time.Delta()) * DirectX::XMMatrixRotationZ(-physics->velocity.x * 0.5F * 3.14F * time.Delta());

	GameObject::Update(input, time);
}

void Player::Render(Renderer& renderer)
{
	GameObject::Render(renderer);
}
