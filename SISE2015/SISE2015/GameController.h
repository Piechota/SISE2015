#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Player.h"

class Pawn;
class Graph;

class GameController
{
private:
	struct PlayerInfo
	{
		Player* player;
		Pawn* pawn;
		DecisionInfo currentDecision;
	};

	int numberOfPlayers;
	PlayerInfo* players[6];
	Graph* currentGraph;

	void StartTurn();
	void Turn();
	void EndTurn();
	void RenewData();
	
public:
	GameController();
	void SubmitPlayer(Player* player);
	Graph* graph;

	void MainLoop();

	~GameController();
};

#endif
