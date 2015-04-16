#include "Headers.h"

Color::Color(Uint8 r, Uint8 g, Uint8 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

namespace Colors
{
	const Color white = Color(0xFF, 0xFF, 0xFF);
	const Color black = Color(0x00, 0x00, 0x00);
	const Color red = Color(0xFF, 0x00, 0x00);
	const Color green = Color(0x00, 0xFF, 0x00);
	const Color blue = Color(0x00, 0x00, 0xFF);
}