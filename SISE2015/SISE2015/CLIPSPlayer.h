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

	char* AIfile;
	CLIPS::CLIPSCPPEnv environment;
	CLIPS::DataObject dataObject;

	virtual DecisionInfo ProcessAI(std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) override;
	void AssertPlayerID(uint32_t ID);
	void AssertNodeDistance(uint32_t nodeID, uint32_t playerID, uint32_t distance);
	void AssertNodeNeighbor(uint32_t nodeID, uint32_t neighborID);
};

#endif