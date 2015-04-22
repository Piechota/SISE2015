#include "Headers.h"

Pawn::Pawn()
{
	color = Colors::white;
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
	if (node != nullptr)
	{
		node->SetPawn(nullptr);
	}
}