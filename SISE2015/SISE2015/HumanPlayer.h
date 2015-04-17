#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "Player.h"
class HumanPlayer :
    public Player
{
public:
    virtual Decision ProcessAI(int grapthInfo) override;

    virtual Decision ProcessAI(Node * my_node) override;
    HumanPlayer(std::string name);
    ~HumanPlayer();
};

#endif
