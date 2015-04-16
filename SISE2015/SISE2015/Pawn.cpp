#include "Pawn.h"

Pawn::Pawn()
{
	this->color = Colors::white;
	radius = 10;
}

Pawn::~Pawn()
{

}

void Pawn::CommitSuicide()
{
	this->node->pawn = nullptr;
}