#ifndef _FUZZY_H_
#define _FUZZY_H_
#include "Headers.h"

using namespace fl;

class FuzzyPlayer : public Player
{
protected:
	Engine* engine;
	size_t AddVariables(const std::string* playersNames, const NodeInfo* const checkNode, const size_t playersCount);
public:
	FuzzyPlayer(const std::string& name, const Colour& color);
	~FuzzyPlayer();

	virtual DecisionInfo ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn) override;
};

#endif