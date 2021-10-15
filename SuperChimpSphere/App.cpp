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
}

void App::Update()
{
	time.Tick();
	window.SetTitle(std::to_string(time.Time()));
}

void App::Render()
{
}
