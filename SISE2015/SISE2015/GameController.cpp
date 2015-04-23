#include "Headers.h"

GameController::GameController() : stats("stats1.csv"), turns(0)
{
}

void GameController::Init()
{
    numberOfPlayers = 0;
    currentGraph = new Graph(2, 6);
    currentGraph->Generate();
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
    GraphRenderer::RenderGraph(currentGraph);
}

void GameController::SaveStats()
{
    stats.SaveToFile();
}

bool GameController::GetIsGameOver() const
{
    return isGameOver;
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

void GameController::SubmitPlayer(Player* const player)
{
    players[numberOfPlayers] = new PlayerInfo();
    PlayerInfo* pPlayer = players[numberOfPlayers];

    pPlayer->player = player;
    pPlayer->pawn = new Pawn();
	pPlayer->pawn->color = player->GetColor();

    stats.AddPlayer(player);
    numberOfPlayers++;

    std::vector<Node*>* nodes = currentGraph->GetNodes();
    size_t nodeIndex = 0;
    nodeIndex = (rand() % (nodes->size() - 1)) + 1;

    pPlayer->pawn->SetNode((*nodes)[nodeIndex]);
    (*nodes)[nodeIndex]->SetPawn(pPlayer->pawn);
}

void GameController::StartTurn()
{
    PlayerInfo* currentPlayer;
    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        currentPlayer = players[i];
        if (currentPlayer->pawn->isAlive)
        {
            //RenewData();
            currentPlayer->currentDecision = currentPlayer->player->ProcessAI(graph, currentPlayer->pawn);
            stats.AddSurvival(currentPlayer->player);
        }
    }
}

void GameController::Turn()
{
    PlayerInfo* pPlayer;

    //Suicides
    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        pPlayer = players[i];
        if (pPlayer->pawn->isAlive && pPlayer->currentDecision.type == Decision::Type::SUICIDE)
        {
            pPlayer->pawn->Die();
            stats.AddDeath(pPlayer->player);
        }
    }

    //Moves
    for (size_t i = 0; i < numberOfPlayers; ++i)
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
    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        pPlayer = players[i];

        if (pPlayer->pawn->isAlive && pPlayer->currentDecision.type == Decision::Type::SHOOT)
        {
            Node* targetNode = currentGraph->GetNodeById(pPlayer->currentDecision.target->GetId());

            if (pPlayer->pawn->GetNode()->IsConnectedTo(targetNode) == true) //if target is connected to current node
            {
                if (targetNode->GetPawn() != nullptr)
                {
                    for (size_t j = 0; j < numberOfPlayers; ++j)
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
    for (size_t i = 0; i < numberOfPlayers; ++i)
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

    size_t countAlive = 0;
    for (size_t i = 0; i < numberOfPlayers; ++i)
    {
        if (players[i]->pawn->isAlive)
        {
            countAlive++;
        }
    }

    turns++;

    if (countAlive <= 1 || turns >= 100)
    {
        GameOver();
    }
}

void GameController::GameOver()
{
    isGameOver = true;
    std::cout << "\n\nGAME OVER\n\n";
}

void GameController::RenewData()
{
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
