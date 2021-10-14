#pragma once
#include <bitset>
class Mouse
{
public:
	bool GetButton(int button);
	float GetX();
	float GetY();
	void SetButton(int button, bool state);
	void SetPosition(float _x, float _y);
private:
	static constexpr unsigned int NUMBER_OF_BUTTONS = 3u;
	std::bitset<NUMBER_OF_BUTTONS> current_state;
	float x, y;
};

