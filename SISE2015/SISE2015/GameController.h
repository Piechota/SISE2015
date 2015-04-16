#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Player.h"

class GameController
{
private:
	struct PlayerInfo
	{
		bool currentlyMoving = false;
		Player* player;
		DecisionInfo currentDecision;
	};

	int numberOfPlayers;
	PlayerInfo* players[6];

	void StartTurn();
	void Turn();
	void EndTurn();
	void RenewData();
	
public:
	GameController();
	void SubmitPlayer(Player* player);

	void MainLoop();

	~GameController();
};

#endif
