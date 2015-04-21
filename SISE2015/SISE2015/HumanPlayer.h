#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(std::string name);
	~HumanPlayer();

	virtual DecisionInfo ProcessAI(GraphInfo* grapthInfo, Pawn* myPawn) override;
};

#endif
