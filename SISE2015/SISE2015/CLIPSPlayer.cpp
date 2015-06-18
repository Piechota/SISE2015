#include "CLIPSPlayer.h"

CLIPSPlayer::CLIPSPlayer(const std::string& name, const Colour& color, char* file) : Player(name, color)
{
	AIfile = file;
}

CLIPSPlayer::CLIPSPlayer(const CLIPSPlayer& other) : Player(other)
{

}

DecisionInfo CLIPSPlayer::ProcessAI(std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) {
	// load data (rules), reset
	environment.Clear();
	environment.Load(AIfile);
	environment.Reset();


	// assert player ID
	AssertPlayerID(this->GetId());

	// assert distance info
	for (uint32_t i = 0; i < graphInfo.size(); i++) {
		for (uint32_t a = 0; a < graphInfo[i].distanceToPlayers.size(); ++a) {
			AssertNodeDistance(i, a, graphInfo[i].distanceToPlayers[a].distance);
		}
	}

	// assert neighbor info
	for (uint32_t i = 0; i < graphInfo.size(); i++) {
		for (uint32_t a = 0; a < graphInfo[i].neighborIds.size(); ++a) {
			AssertNodeNeighbor(i, graphInfo[i].neighborIds[a]);
		}
	}

	// run & evaluate
	environment.Run(-1);
	dataObject = environment.Eval("(facts)");

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

void CLIPSPlayer::AssertPlayerID(uint32_t ID) {
	std::ostringstream oss;

	oss.str("");
	oss.clear();
	oss << "(CurrentPlayer ";
	oss << ID << ")";

	std::string& tmp = oss.str();
	environment.AssertString(tmp.c_str());
}

void CLIPSPlayer::AssertNodeDistance(uint32_t nodeID, uint32_t playerID, uint32_t distance) {
	std::ostringstream oss;

	oss.str("");
	oss.clear();
	oss << "(NodeDistance ";
	oss << nodeID << " ";
	oss << playerID << " ";
	oss << distance;
	oss << ")";

	std::string& tmp = oss.str();
	environment.AssertString(tmp.c_str());
}

void CLIPSPlayer::AssertNodeNeighbor(uint32_t nodeID, uint32_t neighborID) {
	std::ostringstream oss;
	
	oss.str("");
	oss.clear();
	oss << "(NodeNeighbor ";
	oss << nodeID << " ";
	oss << neighborID;
	oss << ")";

	std::string& tmp = oss.str();
	environment.AssertString(tmp.c_str());
}
