#include "Colour.h"

Colour::Colour(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1.0F)
{
}

Colour::Colour(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a)
{
}

Colour::Colour(int _r, int _g, int _b) : r(static_cast<float>(_r)/255), g(static_cast<float>(_g) / 255), b(static_cast<float>(_b) / 255), a(1.0F)
{
}

Colour::Colour(int _r, int _g, int _b, int _a) : r(static_cast<float>(_r) / 255), g(static_cast<float>(_g) / 255), b(static_cast<float>(_b) / 255), a(static_cast<float>(_a) / 255)
{
}

float* Colour::Array()
{
	float arr[]{ r,g,b,a };
	return arr;
}
