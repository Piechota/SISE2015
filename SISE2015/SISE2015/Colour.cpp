#include "Colour.h"

Colour::Colour(Uint8 r, Uint8 g, Uint8 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Colour::Colour()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

namespace Colours
{
	const Colour white = Colour(0xFF, 0xFF, 0xFF);
	const Colour black = Colour(0x00, 0x00, 0x00);
	const Colour red = Colour(0xFF, 0x00, 0x00);
	const Colour green = Colour(0x00, 0xFF, 0x00);
	const Colour blue = Colour(0x00, 0x00, 0xFF);

	const Colour nodeOuter = Colour(0x5D, 0x7C, 0x6A);
	const Colour nodeInner = Colour(0x35, 0x3E, 0x38);
	const Colour pawn = Colour(0xEF, 0xE7, 0xA0);
	const Colour pawnActive = Colour(0xF0, 0x55, 0x26);
	Colour background = Colour(0x28, 0x26, 0x24);
}