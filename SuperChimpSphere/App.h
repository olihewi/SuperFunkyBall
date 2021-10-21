#pragma once
#include "Window.h"
#include "GameTime.h"
#include "Mesh.h"
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
	std::unique_ptr<Mesh> mesh;
	float ttfps = 0;
};

