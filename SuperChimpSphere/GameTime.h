#pragma once
#include <chrono>
class GameTime
{
	friend class App;
public:
	GameTime();
	float Time();
	float Delta();
private:
	void Tick();
	std::chrono::steady_clock::time_point now;
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::time_point startup;
};

