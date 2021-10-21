#pragma once
#include "GameSettings.h"
#include "Window.h"
#include "GameTime.h"
#include "GameObject.h"
class App
{
public:
	App(const GameSettings& _settings);
	int Play();
private:
	void GameLoop();
	void Update();
	void Render();

	GameSettings settings;
	Window window;
	GameTime time;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	float ttfps = 0;
};

