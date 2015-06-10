#ifndef _CLIPSPLAYER_H_
#define _CLIPSPLAYER_H_

#include "Headers.h"

class CLIPSPlayer : public Player
{
public:
	CLIPSPlayer(const std::string& name, const Colour& color, char* file);
	CLIPSPlayer(const CLIPSPlayer& other);

	char* AIfile;

	virtual DecisionInfo ProcessAI(const GraphInfo* const graphInfo, const Pawn* const myPawn) override;
};

#endif