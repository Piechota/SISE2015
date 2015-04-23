#ifndef _PAWN_H_
#define _PAWN_H_

#include "Headers.h"

class Node;

class Pawn
{
public:
	Pawn();
	~Pawn();

	void Die();
	Node* GetNode() const;
	void SetNode(Node* const node);

	Color color;
	bool isAlive = true;

private:
	Node* node;
};

#endif