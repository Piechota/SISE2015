#include "Headers.h"


GameController::GameController()
{
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

void GameController::StartTurn()
{
	
}

void GameController::Turn()
{

}

void GameController::EndTurn()
{
	
}

void GameController::RenewData()
{
	if (graphData != nullptr)
	{
		delete graphData;
	}

	graphData = new Graph(*graph);
}
