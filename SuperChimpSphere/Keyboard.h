#pragma once
#include <bitset>
#include "Vector3.h"
class Keyboard
{
public:
	bool GetKey(int key);
	void SetKey(int key, bool current);
	Vector2 GetWASD();
private:
	static constexpr unsigned int NUMBER_OF_KEYS = 256u;
	std::bitset<NUMBER_OF_KEYS> keyStates;
};

