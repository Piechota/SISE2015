#pragma once
#include "Headers.h"
class SpierekFuzzy :
	public FuzzyPlayer
{
public:
	SpierekFuzzy(const std::string& name, const Colour& color);
	~SpierekFuzzy();
	virtual DecisionInfo ProcessAI(std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) override;
};

