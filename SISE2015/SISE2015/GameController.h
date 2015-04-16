#pragma once
#include "Pawn"
#include "Player.h"

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

