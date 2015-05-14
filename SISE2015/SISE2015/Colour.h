#ifndef _COLOR_H
#define _COLOR_H

#include <SDL.h>

struct Colour
{
	Uint8 r;
	Uint8 g;
	Uint8 b;

	Colour();
	Colour(Uint8 r, Uint8 g, Uint8 b);
};		  

namespace Colours
{
	extern const Colour white;
	extern const Colour black;
	extern const Colour red;
	extern const Colour green;
	extern const Colour blue;

	extern const Colour nodeOuter;
	extern const Colour nodeInner;
	extern const Colour pawn;
	extern const Colour pawnActive;
	extern Colour background;
}

#endif
