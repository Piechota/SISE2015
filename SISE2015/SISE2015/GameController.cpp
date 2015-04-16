#include "GameController.h"

GameController::GameController()
{
	numberOfPlayers = 0;
}


GameController::~GameController()
{
}

void GameController::MainLoop()
{
	StartTurn();
	Turn();
	EndTurn();
}

void GameController::SubmitPlayer(Player* player)
{
	
	players[numberOfPlayers]->player = player;
	
	numberOfPlayers++;
}

void GameController::StartTurn()
{
	
}

void GameController::Turn()
{
	PlayerInfo* currentPlayer;
	for (unsigned char i = 0; i < numberOfPlayers; ++i)
	{
		currentPlayer = players[i];
		RenewData();
		currentPlayer->currentDecision = currentPlayer->player->ProcessAI(0);
	}
}

void GameController::EndTurn()
{
	
}

void GameController::RenewData()
{
	if (graph != nullptr)
	{
		delete graph;
	}

	graph = new Graph(*currentGraph);
}
