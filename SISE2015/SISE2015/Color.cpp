#include "Color.h"

Color::Color(Uint8 r, Uint8 g, Uint8 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

namespace Colors
{
	const Color white = Color(0xFF, 0xFF, 0xFF);
	const Color black = Color(0x00, 0x00, 0x00);
	const Color red = Color(0xFF, 0x00, 0x00);
	const Color green = Color(0x00, 0xFF, 0x00);
	const Color blue = Color(0x00, 0x00, 0xFF);

	const Color background = Color(0x28, 0x26, 0x24);
	const Color nodeOuter = Color(0x5D, 0x7C, 0x6A);
	const Color nodeInner = Color(0x35, 0x3E, 0x38);
	const Color pawn = Color(0xEF, 0xE7, 0xA0);
	const Color pawnActive = Color(0xF0, 0x55, 0x26);
}