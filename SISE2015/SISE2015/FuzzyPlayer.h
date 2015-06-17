#pragma once
#include "Headers.h"

using namespace fl;

class FuzzyPlayer : public Player
{
	Engine* engine;
public:
	FuzzyPlayer(const std::string& name, const Colour& color);
	~FuzzyPlayer();

	virtual DecisionInfo ProcessAI(std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) override;
};

