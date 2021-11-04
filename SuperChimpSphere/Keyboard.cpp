#include "Keyboard.h"

void Keyboard::HandleKeyDown(WPARAM w, LPARAM l)
{
	keyStates[w] = true;
}

void Keyboard::HandleKeyUp(WPARAM w, LPARAM l)
{
	keyStates[w] = false;
}

bool Keyboard::GetKey(int key)
{
	return keyStates[key];
}
