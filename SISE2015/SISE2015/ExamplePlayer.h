#ifndef _EXAMPLEPLAYER_H_
#define _EXAMPLEPLAYER_H_

#include "Headers.h"

class ExamplePlayer : public Player
{
public:
	ExamplePlayer();
	ExamplePlayer(const ExamplePlayer &other);

	virtual DecisionInfo ProcessAI(GraphInfo grapthInfo);
};

#endif