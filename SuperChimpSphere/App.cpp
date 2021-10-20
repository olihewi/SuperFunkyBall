#include "App.h"

App::App() : window(1080,720,"ASGE")
{
	Mesh::Register(window.GetRenderer());
	mesh = new Mesh (Mesh::CreatePrimitiveCube(window.GetRenderer(), Vector3{ 1.0F,1.0F,1.0F }));
	//mesh = new Mesh(Mesh::CreatePrimitiveSphere(window.GetRenderer(), 0.5F, 4U));
}

int App::Play()
{
	while (true)
	{
		if (const auto errorCode = Window::ProcessMessages())
		{
			return *errorCode;
		}
		GameLoop();
	}
	return -1;
}

void App::GameLoop()
{
	Update();
	Render();
	window.GetRenderer().EndFrame();
	//window.GetRenderer().RenderTestTriangle(time.Time());
}

void App::Update()
{
	time.Tick();
}

void App::Render()
{
	const float t = -time.Time();
	const float r = sinf(t) / 2.0F + 0.5F;
	const float g = sinf(t + 2.0F) / 2.0F + 0.5F;
	const float b = sinf(t + 4.0F) / 2.0F + 0.5F;
	window.GetRenderer().SetBackground(Colour(r, g, b));
	mesh->Render(window.GetRenderer());
}
