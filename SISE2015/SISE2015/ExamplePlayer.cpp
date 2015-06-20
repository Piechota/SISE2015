#include "Headers.h"

ExamplePlayer::ExamplePlayer(const std::string& name, const Colour& color) : Player(name, color)
{

}

ExamplePlayer::ExamplePlayer(const ExamplePlayer& other) : Player(other)
{
	
}

DecisionInfo ExamplePlayer::ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn)
{
	//throw 0;
	Decision dec;
	//dec.type = (Decision::Type) ((rand() % 10 + time(NULL) % 25) % (int)(Decision::COUNT));
	dec.type = Decision::Type::MOVE;
	const Node* const myNode = myPawn->GetNode();
	const std::vector<Node*>* const connections = myNode->GetConnections();
	dec.target = (*connections)[ (rand() % 12 + time(NULL) % 31) % (connections->size())];
	return dec;
}