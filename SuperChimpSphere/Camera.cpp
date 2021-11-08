#include "Camera.h"

Camera::Camera(Renderer& renderer, Player* _player) : player(_player)
{
	transform.position = Vector3(0.0F, 1.0F, 5.0F);
	//transform.rotation.x = -1.0F;
	//transform = renderer.GetViewMatrix();
}

void Camera::Update(Input& input, GameTime& time)
{
	cameraOffset += input.GetAxis(0U,Controller::Axes::LeftTrigger) - input.GetAxis(0U,Controller::Axes::RightTrigger);
	transform.position.x = player->transform.position.x;
	transform.position.y = player->transform.position.y + 0.5F;
	transform.position.z = player->transform.position.z + cameraOffset;

	Vector2 camera = input.GetCamera() * 0.5F * time.Delta();
	rotation += camera;
	/*auto input = keyboard.GetIJKL() * (keyboard.GetKey(16) ? 2.0F : 1.0F);
	auto input2 = keyboard.GetArrowKeys() * time.Delta();

	transform = DirectX::XMMatrixTranslation(-input.x * time.Delta(), 0.0F, input.y * time.Delta()) * transform;
	transform = transform * DirectX::XMMatrixRotationRollPitchYaw(input2.y, input2.x, 0.0F)// transform;*/
	//transform *= DirectX::XMMatrixTranslation(-input.x * time.Delta(), (keyboard.GetKey('O') ? 1.0F : keyboard.GetKey('U') ? -1.0F : 0.0F) * time.Delta(), input.y * time.Delta());
	//transform.rotation.x += time.Delta();
}

void Camera::Render(Renderer& renderer)
{
	DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();
	matrix *= DirectX::XMMatrixTranslation(-transform.position.x, -transform.position.y, 0.0F);
	matrix *= DirectX::XMMatrixRotationX(0.5F);
	matrix *= DirectX::XMMatrixRotationZ(-player->acceleration.x * 5.0F) * DirectX::XMMatrixRotationX(-player->acceleration.y * 5.0F);
	matrix *= DirectX::XMMatrixTranslation(0.0F, 0.0F, -transform.position.z);
	//matrix *= DirectX::XMMatrixRotationY(rotation.x) * DirectX::XMMatrixRotationX(-rotation.y);// *matrix;
	//matrix *= DirectX::XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);// * matrix;
	matrix *= DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
	renderer.SetViewMatrix(matrix);
}
