#include "Pawn.h"

Pawn::Pawn()
{
	this->color = Colors::white;
	radius = 10;
}

Pawn::~Pawn()
{

}

Node* Pawn::GetNode()
{
	return this->node;
}

void Pawn::SetNode(Node* node)
{
	this->node = node;
}

void Pawn::CommitSuicide()
{
	this->node->GetNode()->pawn;
}