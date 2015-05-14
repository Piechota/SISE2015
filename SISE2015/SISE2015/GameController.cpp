#include "Headers.h"

#define MAX_ROUNDS 3
#define MAX_TURNS_PER_ROUND 100
#define GRAPH_DEPTH 2
#define GRAPH_PLAYERS 8

GameController::GameController()
{
}

void GameController::Init()
{
	rounds = MAX_ROUNDS;
	currentRound = 0;
	NextRound();
}

void GameController::NextRound() 
{
	currentRound++;
    numberOfPlayers = 0;
	turns = 0;

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

	if (stats != nullptr)
	{
		delete stats;
	}
	stats = new Stats("stats.csv");

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

	currentGraph = new Graph(GRAPH_DEPTH, GRAPH_PLAYERS);
	currentGraph->Generate();

    SubmitPlayer(new HumanPlayer("gracz #1", Colours::blue));
    SubmitPlayer(new HumanPlayer("gracz #2", Colours::red));
    SubmitPlayer(new HumanPlayer("gracz #3", Colours::white));
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

	if (stats != nullptr)
	{
		delete stats;
		stats = nullptr;
	}
}

void GameController::Render() const
{
    GraphRenderer::RenderBackground();
    GraphRenderer::RenderGraph(currentGraph);
}

void GameController::SaveStats()
{
    stats->SaveToFile();
}

bool GameController::GetIsGameOver() const
{
    return isGameOver;
}

bool GameController::GetIsQuitting() const
{
    return isQuitting;
}

void GameController::MainLoop()
{
    if (!isGameOver && !isQuitting) 
	{
        StartTurn();
        Turn();
        EndTurn();
    }
}

void GameController::SubmitPlayer(Player* const player)
{
    players[numberOfPlayers] = new PlayerInfo();
    PlayerInfo* pPlayer = players[numberOfPlayers];

    pPlayer->player = player;
    pPlayer->pawn = new Pawn();
    pPlayer->pawn->color = player->GetColor();

	stats->AddPlayer(player);
    printf("Submitted new player: %s (%d)\n", pPlayer->player->GetName().c_str(), numberOfPlayers);

    numberOfPlayers++;

    std::vector<Node*>* const nodes = currentGraph->GetNodes();
    size_t nodeIndex = 0;
    nodeIndex = (rand() % (nodes->size() - 1)) + 1;

    pPlayer->pawn->SetNode((*nodes)[nodeIndex]);
    (*nodes)[nodeIndex]->SetPawn(pPlayer->pawn);

    printf("%s's pawn spawned at node %d\n", pPlayer->player->GetName().c_str(), pPlayer->pawn->GetNode()->GetId());
}

Pawn* GameController::GetCurrentPawn() const 
{
	return currentPawn;
}

uint8_t GameController::GetCurrentRoundID() const 
{
	return currentRound;
}

void GameController::StartTurn()
{
    printf("\nStart phase started (%d)\n", turns);

    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        PlayerInfo* const currentPlayer = players[i];

        if (!isQuitting) 
		{
			currentPawn = currentPlayer->pawn;

			if (currentPawn->isAlive)
			{
                //RenewData();
				printf("%s is processing AI", currentPlayer->player->GetName().c_str());
				currentPlayer->currentDecision = currentPlayer->player->ProcessAI(graph, currentPawn);
				stats->AddSurvival(currentPlayer->player);
            }
        }
        else 
		{
            currentPlayer->pawn->Die();
        }
    }
}

void GameController::Turn()
{
    PlayerInfo* pPlayer;
    printf("\nRules phase started\n");

    //Suicides
    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        pPlayer = players[i];

        if (pPlayer->pawn->isAlive && pPlayer->currentDecision.type == Decision::Type::SUICIDE)
        {
            printf("%s commited a suicide\n", pPlayer->player->GetName().c_str());
            pPlayer->pawn->Die();
			stats->AddDeath(pPlayer->player);
        }
    }

    //Moves
    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        pPlayer = players[i];

        if (pPlayer->pawn->isAlive && pPlayer->currentDecision.type == Decision::Type::MOVE)
        {
            Node* const targetNode = currentGraph->GetNodeById(pPlayer->currentDecision.target->GetId());

            if (CanMoveTo(targetNode, pPlayer))
            {
                pPlayer->pawn->GetNode()->SetPawn(nullptr);
                pPlayer->pawn->SetNode(targetNode);
                targetNode->SetPawn(pPlayer->pawn);

                printf("%s moved to %d\n", pPlayer->player->GetName().c_str(), pPlayer->pawn->GetNode()->GetId());
            }
            else
            {
                printf("%s can't move to %d\n", pPlayer->player->GetName().c_str(), pPlayer->pawn->GetNode()->GetId());
            }
        }
    }

    //Shots
    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        pPlayer = players[i];

        if (pPlayer->pawn->isAlive && pPlayer->currentDecision.type == Decision::Type::SHOOT)
        {
            const Node* const targetNode = currentGraph->GetNodeById(pPlayer->currentDecision.target->GetId());

            if (pPlayer->pawn->GetNode()->IsConnectedTo(targetNode) == true) //if target is connected to current node
            {
                if (targetNode->GetPawn() != nullptr)
                {
                    for (size_t j = 0; j < numberOfPlayers; ++j)
                    {
                        if (players[j]->pawn->GetNode() == targetNode->GetPawn()->GetNode())
                        {
                            players[j]->die = true;
							stats->AddKill(pPlayer->player);
                            printf("%s killed player %s\n", pPlayer->player->GetName().c_str(), players[j]->player->GetName().c_str());
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
    printf("\nClean up phase started\n");

    //Finish shots
    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        pPlayer = players[i];

        if (pPlayer->pawn->isAlive)
        {
            if (pPlayer->die)
            {
                pPlayer->pawn->Die();
				stats->AddDeath(pPlayer->player);
                printf("%s died\n", pPlayer->player->GetName().c_str());
            }
        }
    }

    size_t countAlive = 0;

    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        if (players[i]->pawn->isAlive)
        {
            countAlive++;
        }
    }

    turns++;

	if (countAlive <= 1 || turns >= MAX_TURNS_PER_ROUND)
    {
        printf("\nGame Over\n");

        if (countAlive <= 1)
        {
            printf("No more than one player is alive\n");

			for (size_t i = 0; i < numberOfPlayers; ++i)
            {
				if (players[i]->pawn->isAlive)
				{
					printf("s% (%d)\n", players[i]->player->GetName().c_str(), players[i]->player->GetId());
				}
            }
        }
        else
        {
            printf("Turns limit reached\n");
        }

        FinishRound();
    }
}

void GameController::FinishRound() 
{
	if (currentRound < rounds) 
	{
		NextRound();
	}
	else 
	{
		GameOver();
		// TODO: sum up results
	}
}

void GameController::GameOver()
{
    isGameOver = true;
    std::cout << "\n\nGAME OVER\n\n";
}

void GameController::ForceQuit() 
{
    isQuitting = true;
	currentRound = rounds;
}

void GameController::RenewData()
{
	// Currently doesn't work properly, requires graph deep copy!
    if (graph != nullptr)
    {
        delete graph;
    }

    graph = new Graph(*currentGraph);
}

bool GameController::CanMoveTo(const Node* const node, const PlayerInfo* const player) const
{
    if (player->pawn->GetNode()->IsConnectedTo(node) == false) //if target is connected to current node
    {
        return false;
    }
    else
    {
        if (node->GetPawn() == nullptr) //if no one is on the node
        {
            for (size_t j = 0; j < numberOfPlayers; ++j) //two pawns try to go to the same node
            {
                if ((player != players[j]) && (players[j]->currentDecision.type == Decision::Type::MOVE))
                {
                    const Node* const pNodeTrg = players[j]->currentDecision.target;

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
