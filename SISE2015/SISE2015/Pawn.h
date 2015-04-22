#ifndef _PAWN_H_
#define _PAWN_H_

#include "Headers.h"

class Node;

class Pawn
{
private:
	Node* node;

public:
	Pawn();
	~Pawn();

	void Die();
	Node* GetNode() const;
	void SetNode(Node* const node);

	bool isAlive = true;
	Color color;
};

#endif