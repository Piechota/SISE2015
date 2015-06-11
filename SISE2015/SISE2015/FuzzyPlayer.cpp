#include "FuzzyPlayer.h"

FuzzyPlayer::FuzzyPlayer(const std::string& name, const Colour& color) : Player(name, color)
{
	Engine* engine = new Engine();

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
		"The following errors were encountered:\n" + status, FL_AT);
}


FuzzyPlayer::~FuzzyPlayer()
{
	delete engine;
}

DecisionInfo CLIPSPlayer::ProcessAI(const GraphInfo* const graphInfo, const Pawn* const myPawn)
{


}