#include "Mouse.h"

bool Mouse::GetButton(int button)
{
    return current_state[button];
}

Vector2 Mouse::GetPos()
{
    return pos;
}

void Mouse::SetButton(int button, bool state)
{
    current_state[button] = state;
}

void Mouse::HandleLButtonDown(WPARAM w, LPARAM l)
{
    current_state[0] = true;
}

void Mouse::HandleLButtonUp(WPARAM w, LPARAM l)
{
    current_state[0] = false;
}

void Mouse::HandleRButtonDown(WPARAM w, LPARAM l)
{
    current_state[1] = true;
}

void Mouse::HandleRButtonUp(WPARAM w, LPARAM l)
{
    current_state[1] = false;
}

void Mouse::HandleMButtonDown(WPARAM w, LPARAM l)
{
    current_state[2] = true;
}

void Mouse::HandleMButtonUp(WPARAM w, LPARAM l)
{
    current_state[2] = false;
}

void Mouse::HandleMouseMove(WPARAM w, LPARAM l)
{
    POINTS pt = MAKEPOINTS(l);
    pos = Vector2(pt.x, pt.y);
}
