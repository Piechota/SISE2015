#include "CLIPSPlayer.h"

CLIPSPlayer::CLIPSPlayer(const std::string& name, const Colour& color, char* file) : Player(name, color)
{
	AIfile = file;
}

CLIPSPlayer::CLIPSPlayer(const CLIPSPlayer& other) : Player(other)
{
	AIfile = other.AIfile;
}

DecisionInfo CLIPSPlayer::ProcessAI(const std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) {
	// load data (rules), reset
	environment.Clear();
	environment.Load(AIfile);
	environment.Reset();

	// assert player ID
	AssertPlayerID(GetId());

	const size_t graphInfoSize = graphInfo.size();

	// assert distance info
	for (size_t i = 0; i < graphInfoSize; ++i)
	{
		for (size_t a = 0; a < graphInfo[i].distanceToPlayers.size(); ++a)
		{
			AssertNodeDistance(i, a, graphInfo[i].distanceToPlayers[a].distance);
		}
	}

	// assert neighbor info
	for (size_t i = 0; i < graphInfoSize; ++i)
	{
		for (size_t a = 0; a < graphInfo[i].neighborIds.size(); ++a)
		{
			AssertNodeNeighbor(i, graphInfo[i].neighborIds[a]);
		}
	}

	// run
	environment.Run(-1);

	// get decision type
	Decision dec;
	//dataObject = environment.Eval("(facts)");			// run this if you want to see all facts
	dataObject = environment.Eval("?*Decision*");
	const CLIPS::SymbolValue* const str = dynamic_cast<CLIPS::SymbolValue*>(dataObject.GetDOValue());
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
	const CLIPS::IntegerValue* const target = dynamic_cast<CLIPS::IntegerValue*>(dataObject.GetDOValue());
	const __int64 decTarget = target->theInteger;

	// This validation is not only not needed, it is actually wrong,
	// but we currently don't have any convenient way of getting node pointer by its id from here.
	const Node* const myNode = myPawn->GetNode();
	const std::vector<Node*>* const connections = myNode->GetConnections();
	const size_t connectionsSize = connections->size();
	bool nodeIdMatched = false;
	for (size_t i = 0; i < connectionsSize; ++i) 
	{
		if ((*connections)[i]->GetId() == target->theInteger) 
		{
			dec.target = (*connections)[i];
			nodeIdMatched = true;
			break;
		}
	}

	if (!nodeIdMatched)
	{
		dec.target = (*connections)[0];
		//dec.target = nullptr;
	}

	// debug fact info
	//dataObject = environment.Eval("(facts)");			// run this if you want to see all facts
	//char* text = "";
	//dataObject.String(text);
	//printf(text);
	std::cout << std::endl << "DECISION: " << decString << " -> " << decTarget << std::endl;
	getchar();

	return dec;
}

void CLIPSPlayer::AssertPlayerID(const uint32_t ID) {
	std::ostringstream oss;

	oss.str("");
	oss.clear();
	oss << "(CurrentPlayer ";
	oss << ID << ")";

	std::string& tmp = oss.str();
	environment.AssertString(tmp.c_str());
}

void CLIPSPlayer::AssertNodeDistance(const uint32_t nodeID, const uint32_t playerID, const uint32_t distance) {
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

void CLIPSPlayer::AssertNodeNeighbor(const uint32_t nodeID, const uint32_t neighborID) {
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
