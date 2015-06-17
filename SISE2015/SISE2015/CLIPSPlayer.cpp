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

	std::ostringstream oss;

	// assert node info
	for (uint32_t i = 0; i < graphInfo.size(); i++) {
		// distance info
		for (uint32_t a = 0; a < graphInfo[i].distanceToPlayers.size(); ++a) {
			oss.str("");
			oss.clear();
			oss << "(NodeDistance ";					// name
			oss << i << " ";							// node ID
			oss << a << " ";							// player ID
			oss << graphInfo[i].distanceToPlayers[a];	// distance
			oss << ")";

			std::string& tmp = oss.str();
			environment.AssertString(tmp.c_str());
		}

		// neighbor info
		for (uint32_t a = 0; a < graphInfo[i].neighborIds.size(); ++a) {
			oss.str("");
			oss.clear();
			oss << "(NodeNeighbor ";			// name
			oss << i << " ";					// node ID
			oss << graphInfo[i].neighborIds[a];	// neighbor ID
			oss << ")";

			std::string& tmp = oss.str();
			environment.AssertString(tmp.c_str());
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