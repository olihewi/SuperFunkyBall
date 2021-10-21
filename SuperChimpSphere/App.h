#pragma once
#include "Window.h"
#include "GameTime.h"
#include "GameObject.h"
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
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	float ttfps = 0;
};

