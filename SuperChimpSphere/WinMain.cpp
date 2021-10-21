#include "App.h"
#include <iostream>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	App app = App(GameSettings(GameSettings::Video(Vector2(1920.0F,1080.0F),true)));
	return app.Play();
}