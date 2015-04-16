#include "Headers.h"

int Pawn::idCounter = 0;

Pawn::Pawn()
{
	this->id = Pawn::idCounter++;
}
Pawn::Pawn(const Pawn &other)
{
	this->id = other.id;
}
Pawn::~Pawn()
{

}
void Pawn::ResetIdIndexing()
{
	Pawn::idCounter;
}
int Pawn::GetId()
{
	return this->id;
}