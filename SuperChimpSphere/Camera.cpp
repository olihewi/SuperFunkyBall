#include "Camera.h"
#include "Skybox.h"

Camera::Camera(Renderer& renderer)
{
	transform.position = Vector3(0.0F, 1.0F, 2.0F);
	//transform = renderer.GetViewMatrix();
}

void Camera::Update(Input& input, GameTime& time)
{
	/*auto input = keyboard.GetIJKL() * (keyboard.GetKey(16) ? 2.0F : 1.0F);
	auto input2 = keyboard.GetArrowKeys() * time.Delta();

	transform = DirectX::XMMatrixTranslation(-input.x * time.Delta(), 0.0F, input.y * time.Delta()) * transform;
	transform = transform * DirectX::XMMatrixRotationRollPitchYaw(input2.y, input2.x, 0.0F)// transform;*/
	//transform *= DirectX::XMMatrixTranslation(-input.x * time.Delta(), (keyboard.GetKey('O') ? 1.0F : keyboard.GetKey('U') ? -1.0F : 0.0F) * time.Delta(), input.y * time.Delta());
}

void Camera::Render(Renderer& renderer)
{
	//renderer.SetViewMatrix(transform.GetMatrix());
}
