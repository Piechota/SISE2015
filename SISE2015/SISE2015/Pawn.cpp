#include "Pawn.h"
#include "Node.h"

Pawn::Pawn()
{
	this->color = Colors::white;
	radius = 10;
}

Pawn::~Pawn()
{

}

Node* Pawn::GetNode() const
{
	return this->node;
}

void Pawn::SetNode(Node* const node)
{
	this->node = node;
}

void Pawn::CommitSuicide()
{
	this->GetNode()->SetPawn(nullptr);
	isAlive = false;
}