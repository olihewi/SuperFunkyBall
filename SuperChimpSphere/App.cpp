#include "App.h"

App::App() : window(1080,720,"ASGE")
{

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
}

void App::Update()
{
	time.Tick();
	const float t = -time.Time();
	const float r = sinf(t) / 2.0F + 0.5F;
	const float g = sinf(t + 2.0F) / 2.0F + 0.5F;
	const float b = sinf(t + 4.0F) / 2.0F + 0.5F;
	window.GetRenderer().SetBackground(Colour(r, g, b));
}

void App::Render()
{
}
