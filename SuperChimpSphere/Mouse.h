#pragma once
#include <bitset>
#include <Windows.h>
#include "Vector3.h"
class Mouse
{
public:
	void HandleLButtonDown(WPARAM w, LPARAM l);
	void HandleLButtonUp(WPARAM w, LPARAM l);
	void HandleRButtonDown(WPARAM w, LPARAM l);
	void HandleRButtonUp(WPARAM w, LPARAM l);
	void HandleMButtonDown(WPARAM w, LPARAM l);
	void HandleMButtonUp(WPARAM w, LPARAM l);
	void HandleMouseMove(WPARAM w, LPARAM l);
	bool GetButton(int button);
	Vector2 GetPos();
	void SetButton(int button, bool state);
private:
	static constexpr unsigned int NUMBER_OF_BUTTONS = 3u;
	std::bitset<NUMBER_OF_BUTTONS> current_state;
	Vector2 pos;
};

