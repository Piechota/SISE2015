#ifndef _COLOR_H
#define _COLOR_H

#include "Headers.h"

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
}

#endif
