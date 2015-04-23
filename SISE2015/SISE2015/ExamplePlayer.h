#ifndef _EXAMPLEPLAYER_H_
#define _EXAMPLEPLAYER_H_

#include "Headers.h"

class ExamplePlayer : public Player
{
public:
	ExamplePlayer(const std::string name, const Color color);
	ExamplePlayer(const ExamplePlayer& other);

	virtual DecisionInfo ProcessAI(GraphInfo* const grapthInfo, Pawn* const myPawn) override;
};

#endif