#include "Headers.h"

HumanPlayer::HumanPlayer(std::string name) : Player(name)
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
    Node* my_node = myPawn->GetNode();

    Decision d;
    std::cout << "Player: " << name << std::endl;
    std::cout << " 1 - move \n 2 - shoot \n 3 - suicide \n";

    int type;

    do
    {
        std::cin >> type;
    }
    while (type < 1 || type > 3);

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
        std::vector<Node*>* nodes = my_node->GetConnections();
        size_t n = nodes->size();

        std::cout << "\n";

        for (size_t i = 0; i < n; ++i)
        {
            std::cout << i << " Id:" << (*nodes)[i]->GetId() << " X:" << (*nodes)[i]->GetPositionX() << " Y:" << (*nodes)[i]->GetPositionY() << std::endl;
        }

        size_t target;

        do
        {
            std::cin >> target;
        }
        while (target < 0 || target > n - 1);

        d.target = (*nodes)[target];
    }

    clear();
    return d;
}

void HumanPlayer::clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
