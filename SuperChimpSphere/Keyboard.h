#pragma once
#include <bitset>
class Keyboard
{
public:
	bool GetKey(int key);
	void SetKey(int key, bool current);
private:
	static constexpr unsigned int NUMBER_OF_KEYS = 256u;
	std::bitset<NUMBER_OF_KEYS> keyStates;
};

