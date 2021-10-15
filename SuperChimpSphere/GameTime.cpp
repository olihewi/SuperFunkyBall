#include "GameTime.h"

GameTime::GameTime()
{
	now = std::chrono::steady_clock::now();
	last = now;
	startup = now;
}

float GameTime::Time()
{
	return std::chrono::duration<float>(now - startup).count();
}

float GameTime::Delta()
{
	return std::chrono::duration<float>(now - last).count();
}

void GameTime::Tick()
{
	last = now;
	now = std::chrono::steady_clock::now();
}
