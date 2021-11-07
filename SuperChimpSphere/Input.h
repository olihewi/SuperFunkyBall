#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "Window.h"
class Input
{
public:
	Input(Window& window);
	void Tick();
	// Keyboard
	bool GetKey(int key);
	// Mouse
	bool GetMouseButton(int button);
	Vector2 GetMousePos();
	// Controller
	bool GetButton(unsigned int _index, int _button);
	bool GetButtonDown(unsigned int _index, int _button);
	bool GetButtonUp(unsigned int _index, int _button);
	float GetAxis(unsigned int _index, unsigned int _axis);
	Vector2 GetStick(unsigned int _index, unsigned int _stick);
	// Mappings
	Vector2 GetMovement();
	Vector2 GetCamera();
	bool GetPrimaryButton();
	bool GetPrimaryButtonDown();

	Keyboard keyboard{};
	Mouse mouse{};
	Controllers controllers{};
};

