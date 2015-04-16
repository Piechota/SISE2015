#ifndef _PAWN_H_
#define _PAWN_H_

#include "Color.h"

class Node;

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