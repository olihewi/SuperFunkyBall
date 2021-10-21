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
		GetKey('A') ? -1.0F : GetKey('D') ? 1.0F : 0.0F,
		GetKey('S') ? -1.0F : GetKey('W') ? 1.0F : 0.0F);
}
