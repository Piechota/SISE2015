#include "Headers.h"
#include "clipscpp.h"

CLIPSPlayer::CLIPSPlayer(const std::string& name, const Colour& color) : Player(name, color)
{

}

CLIPSPlayer::CLIPSPlayer(const CLIPSPlayer& other) : Player(other)
{

}

DecisionInfo CLIPSPlayer::ProcessAI(const GraphInfo* const graphInfo, const Pawn* const myPawn)
{
	CLIPS::CLIPSCPPEnv theEnv;
	CLIPS::DataObject dataObject;
	char* text = "";

	theEnv.Load("../Behaviour/spierek.clp");
	theEnv.Reset();
	theEnv.Run(-1);
	dataObject = theEnv.Eval("(facts)");
	dataObject.String(text);

	printf(text);
	//getchar();

	//throw 0;
	Decision dec;
	//dec.type = (Decision::Type) ((rand() % 10 + time(NULL) % 25) % (int)(Decision::COUNT));
	dec.type = Decision::Type::MOVE;
	Node* myNode = myPawn->GetNode();
	std::vector<Node*>* connections = myNode->GetConnections();
	dec.target = (*connections)[(rand() % 12 + time(NULL) % 31) % (connections->size())];
	return dec;
	//return (Decision) ( (rand() % 10 + time(NULL) % 25 + graphInfo ) % (int)(Decision::DECISION_COUNT) );
}