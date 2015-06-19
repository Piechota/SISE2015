#include "MatushkaRossiyaFuzzy.h"

MatushkaRossiyaFuzzy::MatushkaRossiyaFuzzy(const std::string& name, const Colour& color) : FuzzyPlayer(name, color)
{
}

MatushkaRossiyaFuzzy::~MatushkaRossiyaFuzzy()
{
}

DecisionInfo MatushkaRossiyaFuzzy::ProcessAI(const std::vector<NodeInfo> graphInfo, const Pawn* const myPawn)
{
	engine->restart();

	const std::string name[] = { "Scum" };

	InputVariable* const input = new InputVariable();
	input->setName("Scum");
	input->setRange(0.0, 5.0);
	input->addTerm(new Trapezoid("CLOSE", 0.0, 0.0, 1.0, 1.0));
	input->addTerm(new Trapezoid("MIDDLE", 1.0, 1.0, 2.0, 3.0));
	input->addTerm(new Trapezoid("FAR", 2.0, 3.0, 5.0, 5.0));
	engine->addInputVariable(input);

	OutputVariable* const output = new OutputVariable();
	output->setName("Glory");
	output->setRange(0.0, 1.0);
	output->addTerm(new Trapezoid("LOW", 0.0, 0.0, 0.3, 0.5));
	output->addTerm(new Triangle("MEDIUM", 0.3, 0.5, 0.7));
	output->addTerm(new Trapezoid("HIGH", 0.5, 0.7, 1.0, 1.0));
	output->setDefaultValue(fl::nan);
	engine->addOutputVariable(output);

	RuleBlock* const rules = new RuleBlock;
	rules->addRule(Rule::parse("if Scum is CLOSE then Glory is HIGH", engine));
	rules->addRule(Rule::parse("if Scum is MIDDLE then Glory is MEDIUM", engine));
	rules->addRule(Rule::parse("if Scum is FAR then Glory is LOW", engine));
	engine->addRuleBlock(rules);
	engine->configure("", "", "Minimum", "Maximum", "Centroid");

	Node* target = nullptr;
	float targetValue = 0.0f;

	this->outputVariable = output;

	const Node* const myNode = myPawn->GetNode();
	const std::vector<Node*>* const connections = myNode->GetConnections();
	const size_t connectionsSize = connections->size();

	AnalyzeBattlefieldSituation(connections, graphInfo, target, targetValue);

	for (size_t i = 0; i < connectionsSize; ++i) 
	{
		const Node* const neighbor = (*connections)[i];
		const std::vector<Node*>* const neighborConnections = neighbor->GetConnections();
		const size_t neighborConnectionsSize = neighborConnections->size();

		AnalyzeBattlefieldSituation(neighborConnections, graphInfo, target, targetValue);
	}

	engine->removeInputVariable("Scum");
	engine->removeOutputVariable("Glory");
	engine->removeRuleBlock(0);

	Decision dec;
	dec.target = target;
	if (targetValue > 0.1f) {
		dec.type = Decision::Type::SHOOT;
	}
	else {
		dec.type = Decision::Type::MOVE;
	}

	return dec;
}

void MatushkaRossiyaFuzzy::AnalyzeBattlefieldSituation(const std::vector<Node*>* const nodes, const std::vector<NodeInfo>& graphInfo, Node*& target, float& targetValue)
{
	const std::string name[] = { "Scum" };

	const size_t nodesSize = nodes->size();
	const size_t graphInfoSize = graphInfo.size();

	Node* temporaryTarget = nullptr;
	float temporaryTargetValue = 0.0f;
	const NodeInfo* temporaryTargetInfo = nullptr;

	for (size_t i = 0; i < nodesSize; ++i)
	{
		temporaryTarget = (*nodes)[i];
		const uint32_t temporaryTargetId = temporaryTarget->GetId();

		for (size_t j = 0; j < graphInfoSize; ++j)
		{
			if (temporaryTargetId == graphInfo[j].myId)
			{
				temporaryTargetInfo = &graphInfo[j];
				break;
			}
		}

		AddVariables(name, temporaryTargetInfo, 1);
		engine->process();
		const float outputValue = (float)outputVariable->getOutputValue();

		if (outputValue > targetValue && temporaryTargetValue < outputValue)
		{
			temporaryTargetValue = outputValue;
			target = temporaryTarget;
			targetValue = temporaryTargetValue;
		}

		std::cout << std::endl << "OUTPUT: " << outputValue;
	}
}