#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Headers.h"

class Stats;

class GameController
{
public:
    GameController();
    ~GameController();

    void Init();
    void SubmitPlayer(Player* const player);
    void MainLoop();
    void Render() const;
    void SaveStats();
    bool GetIsGameOver() const;

private:
	Stats stats;

	struct PlayerInfo
	{
		Player* player;
		Pawn* pawn;
		DecisionInfo currentDecision;
		bool die = false;		
	};

	PlayerInfo* players[6];
	Graph* graph;
	Graph* currentGraph;
	bool isGameOver = false;
	uint8_t numberOfPlayers;
    uint8_t turns;

	void StartTurn();
	void Turn();
	void EndTurn();
	void GameOver();
	void RenewData();
	bool CanMoveTo(Node* const node, PlayerInfo* const player) const;
};

#endif
