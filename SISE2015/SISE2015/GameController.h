#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Player.h"
#include "Stats.h"
class Pawn;
class Graph;

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
	~GameController();

	void Init();
	void SubmitPlayer(Player* player);
	void MainLoop();

	Graph* graph;
};

#endif
