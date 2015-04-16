#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Headers.h"
#include "Graph.h"

class GameController
{
private:
	struct PlayerInfo
	{
		bool currentlyMoving = false;
		Pawn* pawn;
		//Player* player;
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

#endif
