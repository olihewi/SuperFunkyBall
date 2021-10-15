#pragma once
#include "Window.h"
#include "GameTime.h"
class App
{
public:
	App();
	int Play();
private:
	void GameLoop();
	void Update();
	void Render();

	Window window;
	GameTime time;
};
