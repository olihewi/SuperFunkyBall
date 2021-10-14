#include "Keyboard.h"

bool Keyboard::GetKey(int key)
{
	return keyStates[key];
}

void Keyboard::SetKey(int key, bool current)
{
	keyStates[key] = current;
}
