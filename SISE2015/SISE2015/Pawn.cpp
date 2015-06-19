#include "Headers.h"

Pawn::Pawn()
{
	color = Colours::white;
}

Pawn::~Pawn()
{

}

void Pawn::Die()
{
	isAlive = false;
	if (node != nullptr)
	{
		node->SetPawn(nullptr);
	}
}