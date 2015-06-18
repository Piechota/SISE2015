#ifndef NZKFUZZY_H
#define NZKFUZZY_H
#include "Headers.h"

class NizikFuzzy : public FuzzyPlayer
{
public:
	NizikFuzzy(const std::string& name, const Colour& color);
	~NizikFuzzy();
	virtual DecisionInfo ProcessAI(const std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) override;
};

#endif