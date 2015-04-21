#include "Headers.h"

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

DecisionInfo HumanPlayer::ProcessAI(GraphInfo* grapthInfo, Pawn* myPawn)
{
	//throw 0;

	Node* my_node = myPawn->GetNode();


	Decision d;
	std::cout << " 1 - move \n 2 - shoot \n 3 - suicide \n";
	int type;
	do
	{
		std::cin >> type;
	} while (type < 1 || type>3);
	switch (type)
	{
	case 1:
		d.type = Decision::MOVE;
		break;
	case 2:
		d.type = Decision::SHOOT;
		break;
	case 3:
		d.type = Decision::SUICIDE;
		break;
	default: break;
	}

	if (type == 1 || type == 2)
	{
		int n = my_node->GetConnections()->size();
		for (int i = 0; i < n; ++i)
		{
			std::cout << i << " " << my_node->GetConnections()->at(i)->GetId() << " " << my_node->GetConnections()->at(i)->GetPositionX() << " " << my_node->GetConnections()->at(i)->GetPositionY() << std::endl;

		}
		int target;
		do
		{
			std::cin >> target;
		} while (target < 0 || target>n - 1);
		d.target = my_node->GetConnections()->at(target);
	}
	std::cout << "\n\n";
	return d;
}


HumanPlayer::HumanPlayer(std::string name) : Player(name)
{
}


HumanPlayer::~HumanPlayer()
{
}
