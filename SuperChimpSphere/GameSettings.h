#pragma once
#include "Vector3.h"
struct GameSettings
{
	struct Video
	{
		Video(Vector2 _resolution, bool _vSync) : resolution(_resolution), vSync(_vSync) {}
		Vector2 resolution { 1920.0F, 1080.0F };
		bool vSync = true;
	};
	GameSettings(Video _video) : video(_video) {}
	Video video;
};