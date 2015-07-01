#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Headers.h"

#define MAX_PLAYERS 6

class Stats;

class GameController
{
public:
    struct PlayerInfo
    {
        DecisionInfo currentDecision;
        Player* player;
        Pawn* pawn;
        bool die = false;
    };

public:
    GameController();
    ~GameController();

    void Init();
    void SubmitPlayer(Player* const player);
    void MainLoop();
    void Render() const;
    void SaveStats();
    bool GetIsGameOver() const;
    void ForceQuit();
	bool GetIsQuitting() const;
	uint8_t GetCurrentRoundID() const;
    Pawn* GetCurrentPawn() const;

private:
    std::vector<PlayerInfo*> players;
    Pawn* currentPawn;
    Graph* graph;
    Graph* currentGraph;
	Stats* stats;
    bool isGameOver = false;
    bool isQuitting = false;
    uint8_t numberOfPlayers;
    uint8_t turns;
    uint8_t rounds;
    uint8_t currentRound;

	void NextRound();
    void StartTurn();
    void Turn();
    void EndTurn();
    void RenewData();
    bool CanMoveTo(const Node* const node, const PlayerInfo* const player) const;
    void FinishRound();
    void GameOver();
};

#endif
