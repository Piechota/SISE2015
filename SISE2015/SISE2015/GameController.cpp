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
	PlayerInfo* pPlayer = players[numberOfPlayers];	
	pPlayer->player = player;
	pPlayer->pawn = new Pawn();
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
	PlayerInfo* pPlayer;
	//Suicides
	for (int i = 0; i < numberOfPlayers; i++)
	{
		pPlayer = players[i];
		if (pPlayer->currentDecision.type == Decision::Type::SUICIDE)
		{
			pPlayer->pawn->isAlive = false;
			//BpPlayer->pawn->node->pawn = nullptr;
		}
	}

	//Moves
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (players[i]->currentDecision.type == Decision::Type::SHOOT)
		{

		}
	}

	//Shots
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (players[i]->currentDecision.type == Decision::Type::MOVE)
		{

		}
	}

	
}

void GameController::RenewData()
{
	if (graph != nullptr)
	{
		delete graph;
	}

	graph = new Graph(*currentGraph);
}
