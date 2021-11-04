#pragma once
#include <bitset>
#include "Vector3.h"
#include <Windows.h>
class Keyboard
{
public:
	void HandleKeyDown(WPARAM w, LPARAM l);
	void HandleKeyUp(WPARAM w, LPARAM l);
	bool GetKey(int key);
private:
	static constexpr unsigned int NUMBER_OF_KEYS = 256u;
	std::bitset<NUMBER_OF_KEYS> keyStates;
};

