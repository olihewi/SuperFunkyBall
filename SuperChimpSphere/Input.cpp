#include "Input.h"

Input::Input(Window& window)
{
	window.AddMessageSubscriber(WM_KEYDOWN, [this](WPARAM w, LPARAM l) { keyboard.HandleKeyDown(w, l); });
	window.AddMessageSubscriber(WM_KEYUP, [this](WPARAM w, LPARAM l) { keyboard.HandleKeyUp(w, l); });
	window.AddMessageSubscriber(WM_LBUTTONDOWN, [this](WPARAM w, LPARAM l) { mouse.HandleLButtonDown(w, l); });
	window.AddMessageSubscriber(WM_LBUTTONUP, [this](WPARAM w, LPARAM l) { mouse.HandleLButtonUp(w, l); });
	window.AddMessageSubscriber(WM_RBUTTONDOWN, [this](WPARAM w, LPARAM l) { mouse.HandleRButtonDown(w, l); });
	window.AddMessageSubscriber(WM_RBUTTONUP, [this](WPARAM w, LPARAM l) { mouse.HandleRButtonUp(w, l); });
	window.AddMessageSubscriber(WM_MBUTTONDOWN, [this](WPARAM w, LPARAM l) { mouse.HandleMButtonDown(w, l); });
	window.AddMessageSubscriber(WM_MBUTTONUP, [this](WPARAM w, LPARAM l) { mouse.HandleMButtonUp(w, l); });
	window.AddMessageSubscriber(WM_MOUSEMOVE, [this](WPARAM w, LPARAM l) { mouse.HandleMouseMove(w, l); });
}

void Input::Tick()
{
	keyboard.Tick();
	controllers.Tick();
}

bool Input::GetKey(int key)
{
	return keyboard.GetKey(key);
}

bool Input::GetMouseButton(int button)
{
	return mouse.GetButton(button);
}

Vector2 Input::GetMousePos()
{
	return mouse.GetPos();
}

bool Input::GetButton(unsigned int _index, int _button)
{
	return controllers.GetButton(_index, _button);
}

bool Input::GetButtonDown(unsigned int _index, int _button)
{
	return controllers.GetButtonDown(_index, _button);
}

bool Input::GetButtonUp(unsigned int _index, int _button)
{
	return controllers.GetButtonUp(_index, _button);
}

float Input::GetAxis(unsigned int _index, unsigned int _axis)
{
	return controllers.GetAxis(_index, _axis);
}

Vector2 Input::GetStick(unsigned int _index, unsigned int _stick)
{
	return Vector2(GetAxis(_index, _stick), GetAxis(_index, _stick + 1U));
}

Vector2 Input::GetMovement()
{
	Vector2 movement = GetStick(0U, Controller::Sticks::Left) +
		Vector2(static_cast<float>(GetKey('D')) - static_cast<float>(GetKey('A')),
			static_cast<float>(GetKey('W')) - static_cast<float>(GetKey('S')));
	if (movement.Magnitude() > 1.0F)
	{
		movement = movement.Normalized();
	}
	return movement;
}

bool Input::GetPrimaryButton()
{
	return controllers.GetButton(0U,Controller::Buttons::A) || keyboard.GetKey(Keys::Space);
}

bool Input::GetPrimaryButtonDown()
{
	return controllers.GetButtonDown(0U, Controller::Buttons::A) || keyboard.GetKeyDown(Keys::Space);
}
