#include "Camera.h"

Camera::Camera(Renderer& renderer, Player* _player) : player(_player)
{
	transform.position = Vector3(0.0F, 1.0F, 5.0F);
	//transform.rotation.x = -1.0F;
	//transform = renderer.GetViewMatrix();
}

void Camera::Update(Input& input, GameTime& time)
{
	transform.position.x = player->transform.position.x;
	transform.position.y = player->transform.position.y;
	transform.position.z = player->transform.position.z + 5.0F;

	if (input.GetKey(Keys::R))
	{
		transform.rotation.y += 0.1F * time.Delta();
	}
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
	matrix *= DirectX::XMMatrixTranslation(-transform.position.x, -transform.position.y, -transform.position.z);
	matrix *= DirectX::XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);// * matrix;
	matrix *= DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
	renderer.SetViewMatrix(matrix);
}
