#include "Light.h"

Light::Light(Renderer& renderer, Vector3 _direction, Colour _ambient, Colour _diffuse) : direction(_direction), ambient(_ambient), diffuse(_diffuse)
{
	
}

void Light::Render(Renderer& renderer)
{
}
