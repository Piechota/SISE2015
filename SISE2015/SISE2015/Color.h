#ifndef _COLOR_H
#define _COLOR_H

#include <SDL.h>

struct Color
{
	Uint8 r;
	Uint8 g;
	Uint8 b;

	Color();
	Color(Uint8 r, Uint8 g, Uint8 b);
};		  

namespace Colors
{
	extern const Color white;
	extern const Color black;
	extern const Color red;
	extern const Color green;
	extern const Color blue;

	extern const Color background;
	extern const Color nodeOuter;
	extern const Color nodeInner;
	extern const Color pawn;
	extern const Color pawnActive;
}

#endif
