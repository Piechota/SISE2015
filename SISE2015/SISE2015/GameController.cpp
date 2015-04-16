#include "Headers.h"


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
	players[numberOfPlayers] = player;
	numberOfPlayers++;
}

void GameController::StartTurn()
{
	
}

void GameController::Turn()
{
	for (unsigned char i = 0; i < numberOfPlayers; ++i)
	{
		players[i]->ProcessAI(NULL);
	}
}

void GameController::EndTurn()
{
	
}

void GameController::RenewData()
{
	//if (graphData != nullptr)
	//{
	//	delete graphData;
	//}

	//graphData = new Graph(graph);
}
