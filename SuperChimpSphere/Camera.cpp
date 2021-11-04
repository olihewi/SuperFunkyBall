#include "Camera.h"
#include "Skybox.h"

Camera::Camera(Renderer& renderer)
{
	transform = renderer.GetViewMatrix();
}

void Camera::Update(Keyboard& keyboard, GameTime& time)
{
	auto input = keyboard.GetIJKL() * (keyboard.GetKey(16 /*shift*/) ? 2.0F : 1.0F);
	transform *= DirectX::XMMatrixTranslation(-input.x * time.Delta(), (keyboard.GetKey('O') ? 1.0F : keyboard.GetKey('U') ? -1.0F : 0.0F) * time.Delta(), input.y * time.Delta());
}

void Camera::Render(Renderer& renderer)
{
	renderer.SetViewMatrix(transform);
}
