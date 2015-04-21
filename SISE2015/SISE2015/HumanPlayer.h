#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "Headers.h"
class HumanPlayer :
    public Player
{
public:
	virtual DecisionInfo ProcessAI(GraphInfo* grapthInfo, Pawn* myPawn) override;

    HumanPlayer(std::string name);
    ~HumanPlayer();
};

#endif
