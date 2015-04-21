#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Headers.h"

class Stats;

class GameController
{
private:
	Graph* graph;
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
	void Render() const;
	void SaveStats();
};

#endif
