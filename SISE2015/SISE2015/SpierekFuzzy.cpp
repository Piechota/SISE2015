#include "Headers.h"

SpierekFuzzy::SpierekFuzzy(const std::string& name, const Colour& color) : FuzzyPlayer(name, color){}
SpierekFuzzy::~SpierekFuzzy(){}

DecisionInfo SpierekFuzzy::ProcessAI(const std::vector<NodeInfo> graphInfo, const Pawn* const myPawn)
{
	engine->restart();


	// set input data
	const std::string nm[] = { "EnemyDistance" };
	InputVariable* input = new InputVariable();
	input->setName("EnemyDistance");
	input->setRange(0.0, 5.0);
	input->addTerm(new Trapezoid("NEXTTO", 0.0, 0.0, 1.0, 1.0));
	input->addTerm(new Trapezoid("CLOSE", 1.0, 1.0, 2.0, 3.0));
	input->addTerm(new Trapezoid("FAR", 2.0, 3.0, 5.0, 5.0));
	engine->addInputVariable(input);

	// set output data
	OutputVariable* output = new OutputVariable();
	output->setName("Risk");
	output->setRange(0.0, 1.0);
	output->addTerm(new Trapezoid("LOW", 0.0, 0.0, 0.3, 0.5));
	output->addTerm(new Triangle("MEDIUM", 0.3, 0.5, 0.7));
	output->addTerm(new Trapezoid("HIGH", 0.5, 0.7, 1.0, 1.0));
	output->setDefaultValue(fl::nan);
	engine->addOutputVariable(output);

	// set rules
	RuleBlock* rules = new RuleBlock;
	rules->addRule(Rule::parse("if EnemyDistance is NEXTTO then Risk is HIGH", engine));
	rules->addRule(Rule::parse("if EnemyDistance is CLOSE then Risk is MEDIUM", engine));
	rules->addRule(Rule::parse("if EnemyDistance is FAR then Risk is LOW", engine));
	engine->addRuleBlock(rules);
	engine->configure("", "", "Minimum", "Maximum", "Centroid");

	

	// find best node
	Node* target;
	float targetValue = 0;

	Node* neighbor;
	const NodeInfo* neighborInfo;

	for (size_t i = 0; i < myPawn->GetNode()->GetConnections()->size(); ++i) {
		// choose a neighbor and get info
		neighbor = myPawn->GetNode()->GetConnections()->at(i);
		for (size_t j = 0; j < graphInfo.size(); ++j) {
			if (neighbor->GetId() == graphInfo.at(j).myId) {
				neighborInfo = &graphInfo.at(j);
				break;
			}
		}

		// evaluate
		AddVariables(nm, neighborInfo, 1);
		engine->process();
		if (targetValue < output->getOutputValue()) {
			targetValue = (float)output->getOutputValue();
			target = neighbor;
		}

		std::cout << std::endl << "OUTPUT: " << output->getOutputValue();
	}

	engine->removeInputVariable("EnemyDistance");
	engine->removeOutputVariable("Risk");
	engine->removeRuleBlock(0);

	Decision dec;
	dec.target = neighbor;
	if (targetValue > 0.6f) {
		dec.type = Decision::Type::SHOOT;
	}
	else {
		dec.type = Decision::Type::MOVE;
	}

	return dec;
}