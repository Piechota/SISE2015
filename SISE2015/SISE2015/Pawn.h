#ifndef _PAWN_H_
#define _PAWN_H_

#include "Color.h"

class Node;

class Pawn
{
private:
	Node* node;
public:
	Pawn();
	~Pawn();
	bool isAlive = true;

	Node* GetNode();
	void SetNode(Node* node);
	int radius;
	Color color;
	void CommitSuicide();
};

#endif