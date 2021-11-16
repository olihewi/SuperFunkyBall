#include "Camera.h"

Camera::Camera(Renderer& renderer, Player* _player) : player(_player), skybox(renderer,"Textures/Skyboxes/Midday.png")
{
}

void Camera::Update(Input& input, GameTime& time)
{
	transform.position.x = player->transform.position.x;
	transform.position.y = player->transform.position.y + 0.5F;
	transform.position.z = player->transform.position.z;

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

	renderer.SetViewMatrix(matrix * DirectX::XMMatrixRotationY(player->cameraDir.x) * DirectX::XMMatrixRotationX(player->cameraDir.y));
	renderer.SetModelMatrix(matrix);
	skybox.Render(renderer);

	matrix *= DirectX::XMMatrixTranslation(-transform.position.x, -transform.position.y, -player->transform.position.z);
	matrix *= DirectX::XMMatrixRotationY(player->cameraDir.x) * DirectX::XMMatrixRotationX(player->cameraDir.y);
	matrix *= DirectX::XMMatrixRotationZ(-player->cameraTilt.x * 5.0F) * DirectX::XMMatrixRotationX(-player->cameraTilt.y * 5.0F);
	matrix *= DirectX::XMMatrixTranslation(0.0F, 0.0F, -cameraOffset);
	renderer.SetViewMatrix(matrix);
}
