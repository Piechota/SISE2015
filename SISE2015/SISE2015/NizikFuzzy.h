#ifndef NZKFUZZY_H
#define NZKFUZZY_H
#include "Headers.h"

class NizikFuzzy : public FuzzyPlayer
{
public:
	PiechotaFuzzy(const std::string& name, const Colour& color);
	~PiechotaFuzzy();
	virtual DecisionInfo ProcessAI(std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) override;
};

#endif