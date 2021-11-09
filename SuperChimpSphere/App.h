#pragma once
#include "GameSettings.h"
#include "GameTime.h"
#include "GameObject.h"
#include "Input.h"
#include "Level.h"
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
	Input input;
	GameTime time;
	std::unique_ptr<Level> currentLevel;
	std::vector<std::string> levelSequence;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	float ttfps = 0;
};

