#include "GameController.h"
#include "Pawn.h"
#include "Graph.h"

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
			pPlayer->pawn->CommitSuicide();
		}
	}

	//Moves
	for (int i = 0; i < numberOfPlayers; i++)
	{
		pPlayer = players[i];
		if (pPlayer->currentDecision.type == Decision::Type::MOVE)
		{
			bool denyMove = false;
			Node* targetNode = currentGraph->GetNodeById(pPlayer->currentDecision.target->GetId());

			if (pPlayer->pawn->GetNode()->IsConnectedTo(targetNode) == false) //if target is connected to current node
			{
				denyMove = true;
			}
			else
			{
				if (targetNode->GetPawn() == nullptr) //if no one is on the node
				{
					for (int j = 0; j < numberOfPlayers; j++) //two pawns try to go to the same node
					{
						if ((i != j) && (players[j]->currentDecision.type == Decision::Type::MOVE))
						{
							Node* pNodeTrg = players[j]->currentDecision.target;
							if (pNodeTrg->GetId() == pPlayer->currentDecision.target->GetId())
							{
								denyMove = true;
								break;
							}
						}
					}
				}
				else
				{
					denyMove = true; //another pawn is on the node
				}
			}
			
			if (!denyMove)
			{
				pPlayer->pawn->GetNode()->SetPawn(nullptr);
				pPlayer->pawn->SetNode(targetNode);
				targetNode->SetPawn(pPlayer->pawn);
			}
		}
	}

	//Shots
	for (int i = 0; i < numberOfPlayers; i++)
	{
		pPlayer = players[i];
		if (pPlayer->currentDecision.type == Decision::Type::SHOOT)
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
