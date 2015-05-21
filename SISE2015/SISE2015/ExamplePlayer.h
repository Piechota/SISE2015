#ifndef _EXAMPLEPLAYER_H_
#define _EXAMPLEPLAYER_H_

#include "Headers.h"

class ExamplePlayer : public Player
{
public:
	ExamplePlayer(const std::string& name, const Colour& color);
	ExamplePlayer(const ExamplePlayer& other);

	virtual DecisionInfo ProcessAI(const GraphInfo* const grapthInfo, const Pawn* const myPawn) override;
};

#endif