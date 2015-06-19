#ifndef _ROSSIYAFUZZY_H_
#define _ROSSIYAFUZZY_H_
#include "Headers.h"

class MatushkaRossiyaFuzzy : public FuzzyPlayer
{
public:
	MatushkaRossiyaFuzzy(const std::string& name, const Colour& color);
	~MatushkaRossiyaFuzzy();
	virtual DecisionInfo ProcessAI(const std::vector<NodeInfo> graphInfo, const Pawn* const myPawn) override;

private:
	void AnalyzeBattlefieldSituation(const std::vector<Node*>* const nodes, const std::vector<NodeInfo>& graphInfo, Node*& target, float& targetValue);
	OutputVariable* outputVariable;
};

#endif