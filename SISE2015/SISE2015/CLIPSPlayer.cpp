#include "CLIPSPlayer.h"

CLIPSPlayer::CLIPSPlayer(const std::string& name, const Colour& color, char* file) : Player(name, color)
{
	AIfile = file;
}

CLIPSPlayer::CLIPSPlayer(const CLIPSPlayer& other) : Player(other)
{

}

DecisionInfo CLIPSPlayer::ProcessAI(const GraphInfo* const graphInfo, const Pawn* const myPawn)
{
	// load data (rules), reset and run
	theEnv.Load(AIfile);
	theEnv.Reset();
	theEnv.Run(-1);
	
	// assert new facts
	theEnv.AssertString("(Shipment Wood 6)");

	// evaluate (run all rules)
	dataObject = theEnv.Eval("(facts)");

	// display info
	char* text = "";
	dataObject.String(text);
	printf(text);
	getchar();

	// old decision making
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