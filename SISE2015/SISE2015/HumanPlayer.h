#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "Headers.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name);
    ~HumanPlayer();

	virtual DecisionInfo ProcessAI(GraphInfo* const grapthInfo, Pawn* const myPawn) override;
};

#endif
