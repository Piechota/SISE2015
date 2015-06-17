#include "CLIPSPlayer.h"

CLIPSPlayer::CLIPSPlayer(const std::string& name, const Colour& color, char* file) : Player(name, color)
{
	AIfile = file;
}

CLIPSPlayer::CLIPSPlayer(const CLIPSPlayer& other) : Player(other)
{

}

DecisionInfo CLIPSPlayer::ProcessAI(const GraphInfo* const graphInfo, const Pawn* const myPawn) {
	// load data (rules), reset
	environment.Clear();
	environment.Load(AIfile);
	environment.Reset();

	// assert new facts
	environment.AssertString("(NodeA 1)");
	environment.AssertString("(NodeA 2)");
	environment.AssertString("(NodeA 3)");
	environment.AssertString("(NodeB 1)");
	environment.AssertString("(NodeB 3)");

	// run & evaluate
	//environment.Run(-1);
	//dataObject = environment.Eval("(facts)");
	dataObject = environment.FunctionCall("Add", "1 2");
	//dataObject = environment.FunctionCall("Hypotenuse", "1 2");
	//dataObject = environment.FunctionCall("ReturnSum", "");

	// display info
	char* text = "";
	dataObject.String(text);
	printf("\nDECISION: ");
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