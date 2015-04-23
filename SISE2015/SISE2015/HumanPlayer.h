#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "Headers.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(const std::string name, const Color color);
    ~HumanPlayer();

	virtual DecisionInfo ProcessAI(GraphInfo* const grapthInfo, Pawn* const myPawn) override;

private:
    void clear() const;
};

#endif
