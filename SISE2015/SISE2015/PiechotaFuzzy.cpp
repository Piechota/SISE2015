#include "Headers.h"

PiechotaFuzzy::PiechotaFuzzy(const std::string& name, const Colour& color) : FuzzyPlayer(name, color){}
PiechotaFuzzy::~PiechotaFuzzy(){}
DecisionInfo PiechotaFuzzy::ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn)
{
	engine->restart();

    Node* choice = myPawn->GetNode()->GetConnections()->at(0);
	double value = 10.0;

    Node* shootChoice = myPawn->GetNode()->GetConnections()->at(0);
	double shootValue = -1.0;

	const std::string playersNames[] = { "Player1" };

	InputVariable* iv = new InputVariable();
	iv->setName(playersNames[0]);
	iv->setRange(0.0, 5.0);
	iv->addTerm(new Triangle("NEAR", 0.0, 1.0, 1.0));
	iv->addTerm(new Triangle("MIDDLE", 1.0, 3.0, 3.0));
	iv->addTerm(new Triangle("FAR", 2.5, 5.0, 5.0));
	engine->addInputVariable(iv);

	OutputVariable* danger = new OutputVariable;
	danger->setName("Danger");
	danger->setRange(0, 2);
	danger->setDefaultValue(fl::nan);
	danger->addTerm(new Triangle("LOW", 0, 0.5f));
	danger->addTerm(new Triangle("MEDIUM", 0.5f, 1.5f));
	danger->addTerm(new Triangle("HIGH", 1.0f, 2.0f));
	engine->addOutputVariable(danger);

	RuleBlock* ruleblock = new RuleBlock;
	ruleblock->addRule(Rule::parse("if Player1 is NEAR then Danger is HIGH", engine));
	ruleblock->addRule(Rule::parse("if Player1 is MIDDLE then Danger is MEDIUM", engine));
	ruleblock->addRule(Rule::parse("if Player1 is FAR then Danger is LOW", engine));
	engine->addRuleBlock(ruleblock);
	engine->configure("", "", "Minimum", "Maximum", "Centroid");

	std::string status;
	if (!engine->isReady(&status))
		printf("Engine not ready. \nThe following errors were encountered:\n" + *status.c_str());

	const size_t nodesCount = myPawn->GetNode()->GetConnections()->size();
	const size_t nc = graphInfo.size();
	const NodeInfo* ni;
	Node* n;

	for (size_t i = 0; i < nodesCount; ++i)
	{
		n = myPawn->GetNode()->GetConnections()->at(i);
		for (size_t j = 0; j < nc; ++j)
		{
			if (graphInfo.at(j).myId == n->GetId())
			{
				ni = &graphInfo.at(j);
				break;
			}
		}
		AddVariables(playersNames, ni, 1);
		engine->process();
		printf("\nDECISION: ");
		double tmp = danger->getOutputValue();
		std::cout << ' ' << tmp << std::endl;
		if (tmp < value)
		{
			value = tmp;
			choice = n;
		}
		if (tmp > shootValue)
		{
			shootValue = tmp;
			shootChoice = n;
		}
	}
	engine->removeInputVariable("Player1");
	engine->removeOutputVariable("Danger");
	engine->removeRuleBlock(0);
	Decision dec;

	if (shootValue >= 1.4f)
	{
		dec.type = Decision::Type::SHOOT;
		dec.target = shootChoice;
	}
	else
	{
		dec.type = Decision::Type::MOVE;
		dec.target = choice;
	}
	return dec;
}