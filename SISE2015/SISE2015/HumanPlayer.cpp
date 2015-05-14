#include "Headers.h"

HumanPlayer::HumanPlayer(const std::string name, const Color color) : Player(name, color)
{
}

HumanPlayer::~HumanPlayer()
{
}

//Decision HumanPlayer::ProcessAI(Node * my_node)
//{
//    Decision d;
//    std::cout << " 1 - move \n 2 - shoot \n 3 - suicide \n";
//    int type;
//    do
//    {
//        std::cin >> type;
//    } while (type < 1 || type>3);
//    switch (type)
//    {
//    case 1:
//        d.type = Decision::MOVE;
//        break;
//    case 2:
//        d.type = Decision::SHOOT;
//        break;
//    case 3:
//        d.type = Decision::SUICIDE;
//            break;
//    default: break;
//    }
//
//    if (type==1||type==2)
//    {
//        int n = my_node->GetConnections()->size();
//        for (int i = 0; i < n; ++i)
//        {
//            std::cout << i << " " << my_node->GetConnections()->at(i)->GetId() << " " << my_node->GetConnections()->at(i)->GetPositionX() << " " << my_node->GetConnections()->at(i)->GetPositionY() << std::endl;
//
//        }
//        int target;
//        do
//        {
//            std::cin >> target;
//        } while (target < 0 || target>n-1);
//        d.target = my_node->GetConnections()->at(target);
//    }
//    std::cout << "\n\n";
//    return d;
//
//}

DecisionInfo HumanPlayer::ProcessAI(GraphInfo* const grapthInfo, Pawn* const myPawn)
{
    clear();

    const Node* const my_node = myPawn->GetNode();

    if (danceMat->IsDanceMat()) {
        Decision d;
        std::cout << "Player: " << name << std::endl;
        std::cout << " LEFT-UP - move \n UP - shoot \n UP-RIGHT - suicide \n";

        uint8_t type = 0;

        bool pressedLU = false;
        bool pressedU = false;
        bool pressedUR = false;

        while (!pressedLU && !pressedU && !pressedUR)
        {
            RefreshInputAndScreen();
            pressedLU = danceMat->IsKeyDown(DanceMatButtons::LEFT_UP);
            pressedU = danceMat->IsKeyDown(DanceMatButtons::UP);
            pressedUR = danceMat->IsKeyDown(DanceMatButtons::UP_RIGHT);
        }

        if (pressedLU) type = 1;
        if (pressedU) type = 2;
        if (pressedUR) type = 3;

        switch (type)
        {
        case 1:
            d.type = Decision::Type::MOVE;
            break;
        case 2:
            d.type = Decision::Type::SHOOT;
            break;
        case 3:
            d.type = Decision::Type::SUICIDE;
            break;
        default:
            break;
        }

        if (type == 1 || type == 2)
        {
            const std::vector<Node*>* const nodes = my_node->GetConstConnections();
            const size_t n = nodes->size();

            std::cout << "\n\n DANCE!";

            bool danceMoves = false;
            bool canMove = false;

            while (!danceMoves)
            {
                RefreshInputAndScreen();
                if (!danceMat->IsKeyDown(DanceMatButtons::LEFT_UP) && !danceMat->IsKeyDown(DanceMatButtons::UP) && !danceMat->IsKeyDown(DanceMatButtons::UP_RIGHT))
                    canMove = true;

                if (!canMove)
                    continue;

                bool moveU = danceMat->IsKeyDown(DanceMatButtons::UP);
                bool moveR = danceMat->IsKeyDown(DanceMatButtons::RIGHT);
                bool moveD = danceMat->IsKeyDown(DanceMatButtons::DOWN);
                bool moveL = danceMat->IsKeyDown(DanceMatButtons::LEFT);

                bool moveUR = danceMat->IsKeyDown(DanceMatButtons::UP_RIGHT);
                bool moveRD = danceMat->IsKeyDown(DanceMatButtons::RIGHT_DOWN);
                bool moveDL = danceMat->IsKeyDown(DanceMatButtons::DOWN_LEFT);
                bool moveLU = danceMat->IsKeyDown(DanceMatButtons::LEFT_UP);

                int32_t x = my_node->GetPositionX();
                int32_t y = my_node->GetPositionY();
                for (size_t i = 0; i < n; ++i)
                {
                    if (moveU)
                    {
                        if (nodes->at(i)->GetPositionX() == x && nodes->at(i)->GetPositionY() < y)
                        {
                            d.target = nodes->at(i);
                            danceMoves = true;
                            break;
                        }
                    }
                    if (moveD)
                    {
                        if (nodes->at(i)->GetPositionX() == x && nodes->at(i)->GetPositionY() > y)
                        {
                            d.target = nodes->at(i);
                            danceMoves = true;
                            break;
                        }
                    }
                    if (moveL)
                    {
                        if (nodes->at(i)->GetPositionX() < x && nodes->at(i)->GetPositionY() >= y - 2 && nodes->at(i)->GetPositionY() <= y + 2)
                        {
                            d.target = nodes->at(i);
                            danceMoves = true;
                            break;
                        }
                    }
                    if (moveR)
                    {
                        if (nodes->at(i)->GetPositionX() > x && nodes->at(i)->GetPositionY() >= y - 2 && nodes->at(i)->GetPositionY() <= y + 2)
                        {
                            d.target = nodes->at(i);
                            danceMoves = true;
                            break;
                        }
                    }

                    if (moveUR)
                    {
                        if (nodes->at(i)->GetPositionX() > x && nodes->at(i)->GetPositionY() < y)
                        {
                            d.target = nodes->at(i);
                            danceMoves = true;
                            break;
                        }
                    }
                    if (moveRD)
                    {
                        if (nodes->at(i)->GetPositionX() > x && nodes->at(i)->GetPositionY() > y)
                        {
                            d.target = nodes->at(i);
                            danceMoves = true;
                            break;
                        }
                    }
                    if (moveDL)
                    {
                        if (nodes->at(i)->GetPositionX() < x && nodes->at(i)->GetPositionY() > y)
                        {
                            d.target = nodes->at(i);
                            danceMoves = true;
                            break;
                        }
                    }
                    if (moveLU)
                    {
                        if (nodes->at(i)->GetPositionX() < x && nodes->at(i)->GetPositionY() < y)
                        {
                            d.target = nodes->at(i);
                            danceMoves = true;
                            break;
                        }
                    }
                }
            }
        }
        bool moveU = danceMat->IsKeyDown(DanceMatButtons::UP);
        bool moveR = danceMat->IsKeyDown(DanceMatButtons::RIGHT);
        bool moveD = danceMat->IsKeyDown(DanceMatButtons::DOWN);
        bool moveL = danceMat->IsKeyDown(DanceMatButtons::LEFT);

        bool moveUR = danceMat->IsKeyDown(DanceMatButtons::UP_RIGHT);
        bool moveRD = danceMat->IsKeyDown(DanceMatButtons::RIGHT_DOWN);
        bool moveDL = danceMat->IsKeyDown(DanceMatButtons::DOWN_LEFT);
        bool moveLU = danceMat->IsKeyDown(DanceMatButtons::LEFT_UP);

        while (	moveU || moveD || moveL || moveR ||
                moveUR || moveDL || moveLU || moveRD)
        {
            RefreshInputAndScreen();
            moveU = danceMat->IsKeyDown(DanceMatButtons::UP);
            moveR = danceMat->IsKeyDown(DanceMatButtons::RIGHT);
            moveD = danceMat->IsKeyDown(DanceMatButtons::DOWN);
            moveL = danceMat->IsKeyDown(DanceMatButtons::LEFT);

            moveUR = danceMat->IsKeyDown(DanceMatButtons::UP_RIGHT);
            moveRD = danceMat->IsKeyDown(DanceMatButtons::RIGHT_DOWN);
            moveDL = danceMat->IsKeyDown(DanceMatButtons::DOWN_LEFT);
            moveLU = danceMat->IsKeyDown(DanceMatButtons::LEFT_UP);
        }

        return d;
    }

    Decision d;
    std::cout << "Player: " << name << std::endl;
    std::cout << " 1 - move \n 2 - shoot \n 3 - suicide \n";

    uint8_t type = 0;

    bool pressed1 = false;
    bool pressed2 = false;
    bool pressed3 = false;

    while (!pressed1 && !pressed2 && !pressed3) 
    {
        RefreshInputAndScreen();

        pressed1 = keyboard->IsKeyDown(KeyboardButtons::K1);
        pressed2 = keyboard->IsKeyDown(KeyboardButtons::K2);
        pressed3 = keyboard->IsKeyDown(KeyboardButtons::K3);

        if (keyboard->IsKeyDown(KeyboardButtons::ESCAPE)) {
            game->ForceQuit();
            d.type = Decision::Type::SUICIDE;
            break;
        }
    }

    if (pressed1) type = 1;
    if (pressed2) type = 2;
    if (pressed3) type = 3;

    switch (type)
    {
    case 1:
        d.type = Decision::Type::MOVE;
        break;
    case 2:
        d.type = Decision::Type::SHOOT;
        break;
    case 3:
        d.type = Decision::Type::SUICIDE;
        break;
    default:
        break;
    }

    if (type == 1 || type == 2)
    {
        const std::vector<Node*>* const nodes = my_node->GetConstConnections();
        const size_t n = nodes->size();

        std::cout << "\n\nselect node!";

 /*       std::cout << "\n";

        for (size_t i = 0; i < n; ++i)
        {
            std::cout << i << " Id:" << (*nodes)[i]->GetId() << " X:" << (*nodes)[i]->GetPositionX() << " Y:" << (*nodes)[i]->GetPositionY() << std::endl;
        }

        uint8_t target;

        bool targetSelected = false;
        while (!targetSelected)
        {
            RefreshInputAndScreen();

            for (size_t i = 0; i < n; ++i)
            {
                targetSelected = keyboard->IsKeyDown((uint8_t)i);
                if (targetSelected)
                {
                    target = i;
                    break;
                }
            }
        }
*/
    bool click = false;
    SDL_Event e;
    static const int32_t nodeCircleRadius = (screen_height / 16);
    while (!click)
    {
        RefreshInputAndScreen();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                static int32_t x, y;
                SDL_GetMouseState(&x, &y);
                for (size_t i = 0; i < n; ++i)
                {
                    if (x >= nodes->at(i)->GetPositionX() - nodeCircleRadius && x <= nodes->at(i)->GetPositionX() + nodeCircleRadius &&
                        y >= nodes->at(i)->GetPositionY() - nodeCircleRadius && y <= nodes->at(i)->GetPositionY() + nodeCircleRadius)
                    {
                        d.target = nodes->at(i);
                        click = true;
                        break;
                    }
                }
            }
        }
    }
   //     d.target = (*nodes)[target];
   }

    return d;
}

void HumanPlayer::clear() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
