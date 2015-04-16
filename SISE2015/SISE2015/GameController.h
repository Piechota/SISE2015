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
	Graph* graph;

	void StartTurn();
	void Turn();
	void EndTurn();
	void RenewData();
public:
	GameController();

	void MainLoop();
	Graph* graphData;

	~GameController();
};

