#include "Headers.h"

ExamplePawn::ExamplePawn() : Pawn()
{

}

ExamplePawn::ExamplePawn(const ExamplePawn &other) : Pawn(other)
{
	
}

DecisionInfo ExamplePawn::ProcessAI(GraphInfo grapthInfo)
{
	//here goes logic of AI, ease of use as a priority
	return (Decision) ( (rand() % 10 + time(NULL) % 25 + grapthInfo ) % (int)(Decision::DECISION_COUNT) );
}