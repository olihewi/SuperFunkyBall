#include "Keyboard.h"

bool Keyboard::GetKey(int key)
{
	return keyStates[key];
}

void Keyboard::SetKey(int key, bool current)
{
	keyStates[key] = current;
}

Vector2 Keyboard::GetWASD()
{
	return Vector2(
		static_cast<float>(GetKey('D')) - static_cast<float>(GetKey('A')),
		static_cast<float>(GetKey('W')) - static_cast<float>(GetKey('S')));
}

Vector2 Keyboard::GetIJKL()
{
	return Vector2(
		static_cast<float>(GetKey('J')) - static_cast<float>(GetKey('L')),
		static_cast<float>(GetKey('I')) - static_cast<float>(GetKey('K')));
}

Vector2 Keyboard::GetArrowKeys()
{
	return Vector2(
		static_cast<float>(GetKey('H')) - static_cast<float>(GetKey('F')),
		static_cast<float>(GetKey('T')) - static_cast<float>(GetKey('G')));
}
