#include "GameController.h"
#include "Pawn.h"
#include "Node.h"
#include "Graph.h"
#include "GraphRenderer.h"

GameController::GameController() : stats("stats1.csv")
{
}

void GameController::Init()
{
	numberOfPlayers = 0;
	this->currentGraph = new Graph(2, 6, 100.0f);
	this->currentGraph->Generate();
}

GameController::~GameController()
{
	if (graph != nullptr)
	{
		delete graph;
		graph = nullptr;
	}

	if (currentGraph != nullptr)
	{
		delete currentGraph;
		currentGraph = nullptr;
	}

	for (PlayerInfo* p : players)
	{
		if (p != nullptr)
		{
			if (p->player != nullptr)
			{
				delete p->player;
				p->player = nullptr;
			}

			if (p->pawn != nullptr)
			{
				delete p->pawn;
				p->pawn = nullptr;
			}

			delete p;
			p = nullptr;
		}
	}
}

void GameController::Render() const
{
	GraphRenderer::RenderGraph(this->currentGraph);
}

void GameController::SaveStats()
{
	stats.SaveToFile();
}

void GameController::MainLoop()
{
	if (!isGameOver)
	{
		StartTurn();
		Turn();
		EndTurn();
	}
}

void GameController::SubmitPlayer(Player* player)
{	
	players[numberOfPlayers] = new PlayerInfo();
	PlayerInfo* pPlayer = players[numberOfPlayers];	

	pPlayer->player = player;
	pPlayer->pawn = new Pawn();
	numberOfPlayers++;
	stats.AddPlayer(player);

	std::vector<Node*>* nodes = this->currentGraph->GetNodes();
	int nodeIndex = 0;
	nodeIndex = ( rand() % (nodes->size() - 1) )  + 1;

	pPlayer->pawn->SetNode((*nodes)[nodeIndex]);
	(*nodes)[nodeIndex]->SetPawn(pPlayer->pawn);
}

void GameController::StartTurn()
{
	PlayerInfo* currentPlayer;
	for (unsigned char i = 0; i < numberOfPlayers; ++i)
	{
		currentPlayer = players[i];
		if (currentPlayer->pawn->isAlive)
		{
			//RenewData();
			currentPlayer->currentDecision = currentPlayer->player->ProcessAI(this->graph,currentPlayer->pawn);
			stats.AddSurvival(currentPlayer->player);
		}
	}
}

void GameController::Turn()
{
	PlayerInfo* pPlayer;

	//Suicides
	for (int i = 0; i < numberOfPlayers; i++)
	{
		pPlayer = players[i];
		if (pPlayer->pawn->isAlive && pPlayer->currentDecision.type == Decision::Type::SUICIDE)
		{
			pPlayer->pawn->Die();
			stats.AddDeath(pPlayer->player);
		}
	}

	//Moves
	for (int i = 0; i < numberOfPlayers; i++)
	{
		pPlayer = players[i];
		if (pPlayer->pawn->isAlive && pPlayer->currentDecision.type == Decision::Type::MOVE)
		{
			Node* targetNode = currentGraph->GetNodeById(pPlayer->currentDecision.target->GetId());

			if (CanMoveTo(targetNode, pPlayer))
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

		if (pPlayer->pawn->isAlive && pPlayer->currentDecision.type == Decision::Type::SHOOT)
		{
			Node* targetNode = currentGraph->GetNodeById(pPlayer->currentDecision.target->GetId());

			if (pPlayer->pawn->GetNode()->IsConnectedTo(targetNode) == true) //if target is connected to current node
			{
				if (targetNode->GetPawn() != nullptr)
				{
					for (int j = 0; j < numberOfPlayers; j++)
					{
						if (players[j]->pawn->GetNode() == targetNode->GetPawn()->GetNode())
						{
							players[j]->die = true;
							stats.AddKill(pPlayer->player);
							break;
						}
					}
				}
			}
		}
	}
}

void GameController::EndTurn()
{
	PlayerInfo* pPlayer;

	//Finish shots
	for (int i = 0; i < numberOfPlayers; i++)
	{
		pPlayer = players[i];
		if (pPlayer->pawn->isAlive)
		{
			if (pPlayer->die)
			{
				pPlayer->pawn->Die();
				stats.AddDeath(pPlayer->player);				
			}
		}
	}

	int countAlive = 0;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (players[i]->pawn->isAlive)
			countAlive++;
	}

	if (countAlive <= 1)
		GameOver();
}

void GameController::GameOver()
{
	isGameOver = true;
}

void GameController::RenewData()
{
	if (graph != nullptr)
	{
		delete graph;
	}

	graph = new Graph(*currentGraph);
}

bool GameController::CanMoveTo(Node* node, PlayerInfo* player) const
{
	if (player->pawn->GetNode()->IsConnectedTo(node) == false) //if target is connected to current node
	{
		return false;
	}
	else
	{
		if (node->GetPawn() == nullptr) //if no one is on the node
		{
			for (int j = 0; j < numberOfPlayers; j++) //two pawns try to go to the same node
			{
				if ((player != players[j]) && (players[j]->currentDecision.type == Decision::Type::MOVE))
				{
					Node* pNodeTrg = players[j]->currentDecision.target;
					if (pNodeTrg->GetId() == player->currentDecision.target->GetId())
					{
						return false;
					}
				}
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}
