#ifndef _PAWN_H_
#define _PAWN_H_

#include "Headers.h"
#include "Color.h"

class Pawn
{
public:
	Pawn();
	~Pawn();

	Node* node;
	int radius;
	Color color;
};

#endif