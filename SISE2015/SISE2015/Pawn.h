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

	Colour color;
	bool isAlive = true;

private:
	Node* node;
};

FORCEINLINE Node* Pawn::GetNode() const
{
	return node;
}

FORCEINLINE void Pawn::SetNode(Node* const node)
{
	this->node = node;
}

#endif