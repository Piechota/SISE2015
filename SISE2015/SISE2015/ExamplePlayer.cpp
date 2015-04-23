#include "Headers.h"

ExamplePlayer::ExamplePlayer(std::string name) : Player(name)
{

}

ExamplePlayer::ExamplePlayer(const ExamplePlayer& other) : Player(other)
{
	
}

DecisionInfo ExamplePlayer::ProcessAI(GraphInfo* const grapthInfo, Pawn* const myPawn)
{
	//throw 0;
	Decision dec;
	//dec.type = (Decision::Type) ((rand() % 10 + time(NULL) % 25) % (int)(Decision::COUNT));
	dec.type = Decision::Type::MOVE;
	Node* myNode = myPawn->GetNode();
	std::vector<Node*>* connections = myNode->GetConnections();
	dec.target = (*connections)[ (rand() % 12 + time(NULL) % 31) % (connections->size())];
	return dec;
	//return (Decision) ( (rand() % 10 + time(NULL) % 25 + grapthInfo ) % (int)(Decision::DECISION_COUNT) );
}