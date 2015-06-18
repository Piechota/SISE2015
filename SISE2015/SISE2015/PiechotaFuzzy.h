#ifndef _PIECHOTAFUZZY_H_
#define _PIECHOTAFUZZY_H_
#include "Headers.h"

class PiechotaFuzzy : public FuzzyPlayer
{
public:
	PiechotaFuzzy(const std::string& name, const Colour& color);
	~PiechotaFuzzy();
	virtual DecisionInfo ProcessAI(std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) override;
};

#endif