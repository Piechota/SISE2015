#include "Headers.h"

FuzzyPlayer::FuzzyPlayer(const std::string& name, const Colour& color) : Player(name, color)
{
	engine = new Engine("fuzzy_bitch!");
	/*
	InputVariable* suicide = new InputVariable;
	suicide->setName("Surrounding");
	suicide->setRange(0, 5);
	suicide->addTerm(new Triangle("SAFE", 0, 1));
	suicide->addTerm(new Triangle("UNSAFE", 1, 3));
	suicide->addTerm(new Triangle("DANGEROUS", 2, 5));
	engine->addInputVariable(suicide);

	OutputVariable* danger = new OutputVariable;
	danger->setName("Danger");
	danger->setRange(0, 2);
	danger->setDefaultValue(fl::nan);
	danger->addTerm(new Triangle("LOW", 0, 0.5f));
	danger->addTerm(new Triangle("MEDIUM", 0.5f, 1.5f));
	danger->addTerm(new Triangle("HIGH", 1.0f, 2.0f));
	engine->addOutputVariable(danger);

	RuleBlock* rules = new RuleBlock;
	rules->addRule(Rule::parse("if Surrounding is SAFE then Danger is LOW", engine));
	rules->addRule(Rule::parse("if Surrounding if UNSAFE then Danger is MEDIUM", engine));
	rules->addRule(Rule::parse("if Surrounding is DANGEROUS then Danger is HIGH", engine));
	engine->addRuleBlock(rules);

	engine->configure("", "", "Minimum", "Maximum", "Centroid");

	std::string status;
	if (!engine->isReady(&status))
		throw Exception("Engine not ready. "
		"The following errors were encountered:\n" + status, FL_AT);*/
}


FuzzyPlayer::~FuzzyPlayer()
{
}

DecisionInfo FuzzyPlayer::ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn)
{
	engine->restart();
	const std::string names[] = { "Player1", "Player2" };

	InputVariable* pl = new InputVariable();
	pl->setName(names[0]);
	pl->setRange(1, 5);
	pl->addTerm(new Triangle("NEAR", 1, 2));
	pl->addTerm(new Triangle("MIDDLE", 2, 4));
	pl->addTerm(new Triangle("FAR", 4, 5));
	engine->addInputVariable(pl);
	pl = new InputVariable();
	pl->setName(names[1]);
	pl->setRange(1, 5);
	pl->addTerm(new Triangle("NEAR", 1, 2));
	pl->addTerm(new Triangle("MIDDLE", 2, 4));
	pl->addTerm(new Triangle("FAR", 4, 5));
	engine->addInputVariable(pl);

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
	ruleblock->addRule(Rule::parse("if Player2 is MIDDLE then Danger is MEDIUM", engine));
	ruleblock->addRule(Rule::parse("if Player1 is FAR then Danger is LOW", engine));
	engine->addRuleBlock(ruleblock);
	engine->configure("", "", "Minimum", "Maximum", "Centroid");

	std::string status;
	if (!engine->isReady(&status))
		printf("Engine not ready. \nThe following errors were encountered:\n" + *status.c_str());

	const NodeInfo* ni;
	uint32_t n = myPawn->GetNode()->GetConnections()->at(0)->GetId();
	size_t nc = graphInfo.size();
	for (size_t i = 0; i < nc; ++i)
	{
		if (graphInfo.at(i).myId == n)
		{
			ni = &graphInfo.at(i);
			break;
		}
	}

	AddVariables(names, ni, 2);
	engine->process();
	printf("\nDECISION: ");
	double tmp = danger->getOutputValue();
	std::cout << tmp << std::endl;
	//printf(std::to_string(tmp).c_str());
	//printf(str.c_str());
	getchar();
	Decision dec;
	dec.type = Decision::Type::MOVE;
	Node* myNode = myPawn->GetNode();
	std::vector<Node*>* connections = myNode->GetConnections();
	dec.target = (*connections)[(rand() % 12 + time(NULL) % 31) % (connections->size())];
	return dec;
}

size_t FuzzyPlayer::AddVariables(const std::string* playersNames, const NodeInfo* const checkNode, const size_t playersCount)
{
	const std::vector<DistanceToPlayer>& distanceToPlayers = checkNode->distanceToPlayers;
	const size_t loop_stop = distanceToPlayers.size() < playersCount ? distanceToPlayers.size() : playersCount;

	for (size_t i = 0; i < loop_stop; ++i)
	{
		if (distanceToPlayers[i].playerID == id) continue;
		engine->getInputVariable(playersNames[i])->setInputValue(distanceToPlayers[i].distance);
	}

	return loop_stop;
}