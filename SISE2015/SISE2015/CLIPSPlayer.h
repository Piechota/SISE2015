#ifndef _CLIPSPLAYER_H_
#define _CLIPSPLAYER_H_

#include "Headers.h"

class CLIPSPlayer : public Player
{
public:
	CLIPSPlayer(const std::string& name, const Colour& color);
	CLIPSPlayer(const CLIPSPlayer& other);

	virtual DecisionInfo ProcessAI(const GraphInfo* const graphInfo, const Pawn* const myPawn) override;
};

#endif