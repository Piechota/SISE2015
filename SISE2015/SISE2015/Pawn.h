#ifndef _PAWN_H_
#define _PAWN_H_

#include "Headers.h"

//this is temporary, we'll need sth more complex, and not just 4 directions -> waiting for grapth
enum Decision
{
	DO_NTH = 0,
	MOVE_UP = 1,
	MOVE_DOWN = 2,
	MOVE_LEFT = 3,
	MOVE_RIGHT = 4,

	DECISION_COUNT
};

//TODO: swap int with some real type later on
#define GraphInfo int
//this depends on the structure of graph
#define DecisionInfo Decision

class Pawn
{
private:
	static int idCounter;
	int id;
public:
	static void ResetIdIndexing();

	Pawn();
	Pawn(const Pawn &other);
	~Pawn();

	int GetId();

	//method called to launch thought proces of the pawn, returns decision
	virtual DecisionInfo ProcessAI(GraphInfo grapthInfo) = 0;
};

#endif //_PAWN_H_