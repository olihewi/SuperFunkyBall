#include "Colour.h"

Colour::Colour() : r(255), g(255), b(255), a(255)
{
}

Colour::Colour(float _r, float _g, float _b) :
	r(static_cast<unsigned char>(_r * 255)), 
	g(static_cast<unsigned char>(_g * 255)),
	b(static_cast<unsigned char>(_b * 255)),
	a(255)
{
}

Colour::Colour(float _r, float _g, float _b, float _a) :
	r(static_cast<unsigned char>(_r * 255)),
	g(static_cast<unsigned char>(_g * 255)),
	b(static_cast<unsigned char>(_b * 255)),
	a(static_cast<unsigned char>(_a * 255))
{
}

Colour::Colour(int _r, int _g, int _b) :
	r(static_cast<unsigned char>(_r)),
	g(static_cast<unsigned char>(_g)),
	b(static_cast<unsigned char>(_b)),
	a(static_cast<unsigned char>(255))
{
}

Colour::Colour(int _r, int _g, int _b, int _a) :
	r(static_cast<unsigned char>(_r)),
	g(static_cast<unsigned char>(_g)),
	b(static_cast<unsigned char>(_b)),
	a(static_cast<unsigned char>(_a))
{
}

Colour::Colour(unsigned char _r, unsigned char _g, unsigned char _b) :
	r(_r),
	g(_g),
	b(_b),
	a(255)
{
}

Colour::Colour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) :
	r(_r),
	g(_g),
	b(_b),
	a(_a)
{
}

unsigned char* Colour::Array()
{
	unsigned char arr[]{ r,g,b,a };
	return arr;
}
