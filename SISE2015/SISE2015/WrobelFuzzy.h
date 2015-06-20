#ifndef _WROBELFUZZY_H_
#define _WROBELFUZZY_H_
#include "Headers.h"

class WrobelFuzzy : public FuzzyPlayer
{
public:
	WrobelFuzzy(const std::string& name, const Colour& color);
	~WrobelFuzzy();
	virtual DecisionInfo ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn) override;
};

#endif //_WROBELFUZZY_H_