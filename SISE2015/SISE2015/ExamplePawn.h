#ifndef _EXAMPLEPAWN_H_
#define _EXAMPLEPAWN_H_

#include "Headers.h"

class ExamplePawn : public Pawn
{
public:
	ExamplePawn();
	ExamplePawn(const ExamplePawn &other);

	virtual DecisionInfo ProcessAI(GraphInfo grapthInfo);
};

#endif