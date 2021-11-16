#include "GameTime.h"
#include <cmath>

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
	return std::fminf(std::chrono::duration<float>(now - last).count(),0.5F);
}

void GameTime::Tick()
{
	last = now;
	now = std::chrono::steady_clock::now();
}
