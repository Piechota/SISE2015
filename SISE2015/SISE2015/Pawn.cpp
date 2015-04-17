#include "Pawn.h"
#include "Node.h"

Pawn::Pawn()
{
	color = Colors::white;
	radius = 10;
}

Pawn::~Pawn()
{

}

Node* Pawn::GetNode() const
{
	return node;
}

void Pawn::SetNode(Node* const node)
{
	this->node = node;
}

void Pawn::Die()
{
	isAlive = false;
	node->SetPawn(nullptr);
}