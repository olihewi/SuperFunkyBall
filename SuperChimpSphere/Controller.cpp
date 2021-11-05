#include "Controller.h"

void Controllers::Tick()
{
	lastControllers = controllers;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(i, &state) == 0)
		{
			auto& gamepad = state.Gamepad;
			auto& controller = controllers[i];
			controller.connected = true;
			controller.buttons = gamepad.wButtons;
			controller.axis[0] = static_cast<float>(gamepad.sThumbLX) / 32767.0F;
			controller.axis[1] = static_cast<float>(gamepad.sThumbLY) / 32767.0F;
			controller.axis[2] = static_cast<float>(gamepad.sThumbRX) / 32767.0F;
			controller.axis[3] = static_cast<float>(gamepad.sThumbRY) / 32767.0F;
			controller.axis[4] = static_cast<float>(gamepad.bLeftTrigger) / 255.0F;
			controller.axis[5] = static_cast<float>(gamepad.bRightTrigger) / 255.0F;
			continue;
		}
		controllers[i].connected = false;
		controllers[i].buttons = 0x0000;
		controllers[i].axis.fill(0.0F);
	}
}

bool Controllers::IsConnected(unsigned int _index)
{
	return controllers[_index].connected;
}

bool Controllers::GetButton(unsigned int _index, int _button)
{
	return (controllers[_index].buttons &_button ) != 0;
}

bool Controllers::GetButtonDown(unsigned int _index, int _button)
{
	return (controllers[_index].buttons & _button ) != 0 &&
		(lastControllers[_index].buttons & _button ) == 0;
}

bool Controllers::GetButtonUp(unsigned int _index, int _button)
{
	return (controllers[_index].buttons & _button ) == 0 &&
		(lastControllers[_index].buttons & _button ) != 0;
}

float Controllers::GetAxis(unsigned int _index, unsigned int _axis)
{
	return controllers[_index].axis[_axis];
}
