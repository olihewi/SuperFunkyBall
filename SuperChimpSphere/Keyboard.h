#pragma once
#include <bitset>
#include "Vector3.h"
#include <Windows.h>
namespace Keys
{
	constexpr int Space		    = 32;
	constexpr int Apostrophe    = 39;
	constexpr int Comma         = 44;
	constexpr int Minus         = 45;
	constexpr int Period        = 46;
	constexpr int Slash         = 47;
	constexpr int Alpha0        = 48;
	constexpr int Alpha1        = 49;
	constexpr int Alpha2        = 50;
	constexpr int Alpha3        = 51;
	constexpr int Alpha4        = 52;
	constexpr int Alpha5        = 53;
	constexpr int Alpha6        = 54;
	constexpr int Alpha7        = 55;
	constexpr int Alpha8        = 56;
	constexpr int Alpha9        = 57;
	constexpr int Semicolon     = 59;
	constexpr int Equal         = 61;
	constexpr int A             = 65;
	constexpr int B             = 66;
	constexpr int C             = 67;
	constexpr int D             = 68;
	constexpr int E             = 69;
	constexpr int F             = 70;
	constexpr int G             = 71;
	constexpr int H             = 72;
	constexpr int I             = 73;
	constexpr int J             = 74;
	constexpr int K             = 75;
	constexpr int L             = 76;
	constexpr int M             = 77;
	constexpr int N             = 78;
	constexpr int O             = 79;
	constexpr int P             = 80;
	constexpr int Q             = 81;
	constexpr int R             = 82;
	constexpr int S             = 83;
	constexpr int T             = 84;
	constexpr int U             = 85;
	constexpr int V             = 86;
	constexpr int W             = 87;
	constexpr int X             = 88;
	constexpr int Y             = 89;
	constexpr int Z             = 90;
	constexpr int LeftBracket   = 91;
	constexpr int Backslash     = 92;
	constexpr int RightBracket  = 93;
	constexpr int Grave         = 96;
	constexpr int Escape        = 256;
	constexpr int Enter         = 257;
	constexpr int Tab           = 258;
	constexpr int Backspace     = 259;
	constexpr int Delete        = 261;
	constexpr int RightArrow    = 262;
	constexpr int LeftArrow     = 263;
	constexpr int DownArrow     = 264;
	constexpr int UpArrow       = 265;
}
class Keyboard
{
public:
	void HandleKeyDown(WPARAM w, LPARAM l);
	void HandleKeyUp(WPARAM w, LPARAM l);
	void Tick();
	bool GetKey(int key);
	bool GetKeyDown(int key);
private:
	static constexpr unsigned int NUMBER_OF_KEYS = 256u;
	std::bitset<NUMBER_OF_KEYS> pendingKeyStates;
	std::bitset<NUMBER_OF_KEYS> keyStates;
	std::bitset<NUMBER_OF_KEYS> prevKeyStates;
};

