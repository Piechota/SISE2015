#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Headers.h"

class GameController
{
private:
	struct PlayerInfo
	{
		bool currentlyMoving = false;
		Pawn* pawn;
		Player* player;
	};
public:
	GameController();
	~GameController();
};

#endif