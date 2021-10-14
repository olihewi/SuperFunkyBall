#include "Mouse.h"

bool Mouse::GetButton(int button)
{
    return current_state[button];
}

float Mouse::GetX()
{
    return x;
}

float Mouse::GetY()
{
    return y;
}

void Mouse::SetButton(int button, bool state)
{
    current_state[button] = state;
}

void Mouse::SetPosition(float _x, float _y)
{
    x = _x;
    y = _y;
}
