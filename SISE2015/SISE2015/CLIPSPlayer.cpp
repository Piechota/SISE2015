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

	// run
	environment.Run(-1);

	// get decision type
	Decision dec;
	//dataObject = environment.Eval("(facts)");			// run this if you want to see all facts
	dataObject = environment.Eval("?*Decision*");
	CLIPS::SymbolValue* str = dynamic_cast<CLIPS::SymbolValue*>(dataObject.GetDOValue());
	std::string decString;

	if (str->theString == "MOVE") {
		dec.type = Decision::Type::MOVE;
		decString = "MOVE";
	}
	else if (str->theString == "SHOOT") {
		dec.type = Decision::Type::SHOOT;
		decString = "SHOOT";
	}
	else {
		dec.type = Decision::Type::SUICIDE;
		decString = "SUICIDE";
	}
	
	// get target node
	dataObject = environment.Eval("?*Target*");
	CLIPS::IntegerValue* target = dynamic_cast<CLIPS::IntegerValue*>(dataObject.GetDOValue());
	__int64 decTarget = target->theInteger;

	Node* myNode = myPawn->GetNode();
	std::vector<Node*>* connections = myNode->GetConnections();
	for (uint32_t i = 0; i < connections->size(); ++i) {
		if ((*connections)[i]->GetId() == target->theInteger) {
			dec.target = (*connections)[i];
		}
	}

	// debug fact info
	dataObject = environment.Eval("(facts)");			// run this if you want to see all facts
	char* text = "";
	dataObject.String(text);
	printf(text);
	std::cout << std::endl << "DECISION: " << decString << " -> " << decTarget << std::endl;
	getchar();

	return dec;
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
