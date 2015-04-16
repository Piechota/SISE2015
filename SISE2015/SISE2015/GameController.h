#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Player.h"
#include "Graph.h"
#include "Pawn.h"
#include "Stats.h"

class GameController
{
private:
	Stats stats;

	struct PlayerInfo
	{
		Player* player;
		Pawn* pawn;
		DecisionInfo currentDecision;
		bool die = false;		
	};

	int numberOfPlayers;
	PlayerInfo* players[6];
	Graph* currentGraph;
	bool isGameOver = false;

	void StartTurn();
	void Turn();
	void EndTurn();
	void GameOver();
	void RenewData();
	bool CanMoveTo(Node* node, PlayerInfo* player) const;

public:
	GameController();
	void SubmitPlayer(Player* player);
	Graph* graph;

	void MainLoop();

	~GameController();
};

#endif
