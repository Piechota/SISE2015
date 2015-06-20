#ifndef _CLIPSPLAYER_H_
#define _CLIPSPLAYER_H_

#include "Headers.h"
#include "clipscpp.h"
#include <iostream>

class CLIPSPlayer : public Player
{
public:
	CLIPSPlayer(const std::string& name, const Colour& color, char* file);
	CLIPSPlayer(const CLIPSPlayer& other);

	virtual DecisionInfo ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn) override;

private:
	void AssertPlayerID(const uint32_t ID);
	void AssertNodeDistance(const uint32_t nodeID, const uint32_t playerID, const uint32_t distance);
	void AssertNodeNeighbor(const uint32_t nodeID, const uint32_t neighborID);

	char* AIfile;
	CLIPS::CLIPSCPPEnv environment;
	CLIPS::DataObject dataObject;
};

#endif