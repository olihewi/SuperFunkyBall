#include "Keyboard.h"

void Keyboard::HandleKeyDown(WPARAM w, LPARAM l)
{
	pendingKeyStates[w] = true;
}

void Keyboard::HandleKeyUp(WPARAM w, LPARAM l)
{
	pendingKeyStates[w] = false;
}

void Keyboard::Tick()
{
	prevKeyStates = keyStates;
	keyStates = pendingKeyStates;
}

bool Keyboard::GetKey(int key)
{
	return keyStates[key];
}

bool Keyboard::GetKeyDown(int key)
{
	return keyStates[key] && !prevKeyStates[key];
}
