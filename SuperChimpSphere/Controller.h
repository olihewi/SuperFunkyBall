#pragma once
#pragma comment(lib, "XInput.lib") 
#include <Windows.h>
#include <Xinput.h>
#include "Vector3.h"
#include <array>
namespace Controller
{
	namespace Buttons
	{
		constexpr int DPadUp        = 0x0001;
		constexpr int DPadDown      = 0x0002;
		constexpr int DPadLeft      = 0x0004;
		constexpr int DPadRight     = 0x0008;
		constexpr int Start         = 0x0010;
		constexpr int Back          = 0x0020;
		constexpr int LeftStick     = 0x0040;
		constexpr int RightStick    = 0x0080;
		constexpr int LeftShoulder  = 0x0100;
		constexpr int RightShoulder = 0x0200;
		constexpr int A             = 0x1000;
		constexpr int B             = 0x2000;
		constexpr int X             = 0x4000;
		constexpr int Y             = 0x8000;
	}
	namespace Axes
	{
		constexpr unsigned int LeftStickX = 0;
		constexpr unsigned int LeftStickY = 1;
		constexpr unsigned int RightStickX = 2;
		constexpr unsigned int RightStickY = 3;
		constexpr unsigned int LeftTrigger = 4;
		constexpr unsigned int RightTrigger = 5;
	}
	namespace Sticks
	{
		constexpr unsigned int Left  = 0;
		constexpr unsigned int Right = 2;
	}
}
class Controllers
{
	struct Controller
	{
		bool connected{};
		WORD buttons{};
		std::array<float, 6> axis{};
	};
public:
	void Tick();
	bool IsConnected(unsigned int _index);
	bool GetButton(unsigned int _index, int _button);
	bool GetButtonDown(unsigned int _index, int _button);
	bool GetButtonUp(unsigned int _index, int _button);
	float GetAxis(unsigned int _index, unsigned int _axis);
private:
	std::array<Controller, XUSER_MAX_COUNT> controllers{};
	std::array<Controller, XUSER_MAX_COUNT> lastControllers{};
};
