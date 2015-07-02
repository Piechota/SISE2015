#include "MatushkaRossiyaFuzzy.h"

MatushkaRossiyaFuzzy::MatushkaRossiyaFuzzy(const std::string& name, const Colour& color) : FuzzyPlayer(name, color)
{
}

MatushkaRossiyaFuzzy::~MatushkaRossiyaFuzzy()
{
}

DecisionInfo MatushkaRossiyaFuzzy::ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn)
{
	std::cout << std::endl << "For the Motherland!";

	engine->restart();

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

	RuleBlock* const rules = new RuleBlock();
	rules->addRule(Rule::parse("if Scum is CLOSE then Glory is HIGH", engine));
	rules->addRule(Rule::parse("if Scum is MIDDLE then Glory is MEDIUM", engine));
	rules->addRule(Rule::parse("if Scum is FAR then Glory is LOW", engine));
	engine->addRuleBlock(rules);
	engine->configure("", "", "Minimum", "Maximum", "Centroid");

	Node* target = nullptr;
	float targetValue = 0.0f;

	const Node* const myNode = myPawn->GetNode();
	const std::vector<Node*>* const connections = myNode->GetConnections();
	const size_t connectionsSize = connections->size();

	AnalyzeBattlefieldSituation(connections, graphInfo, output, target, targetValue);

	Node* targetCopy = target;

	for (size_t i = 0; i < connectionsSize; ++i) 
	{
		const Node* const neighbor = (*connections)[i];
		const std::vector<Node*>* const neighborConnections = neighbor->GetConnections();
		const size_t neighborConnectionsSize = neighborConnections->size();

		AnalyzeBattlefieldSituation(neighborConnections, graphInfo, output, target, targetValue);

		if (target != targetCopy)
		{
			target = const_cast<Node*>(neighbor);
		}
	}

	engine->removeInputVariable("Scum");
	engine->removeOutputVariable("Glory");
	engine->removeRuleBlock(0);

	Decision dec;
	dec.target = target;
	if (targetValue > 0.1f) {
		dec.type = Decision::Type::SHOOT;

		std::cout << std::endl << "I will open fire!";
	}
	else {
		dec.type = Decision::Type::MOVE;

		std::cout << std::endl << "I shall charge forward!";
	}

	//delete input;
	//delete output;
	//delete rules;

	std::cout << std::endl << "Onwards, for glory!" << std::endl << std::endl;

	return dec;
}

void MatushkaRossiyaFuzzy::AnalyzeBattlefieldSituation(const std::vector<Node*>* const nodes, const std::vector<NodeInfo>& graphInfo, const OutputVariable* const outputVariable, Node*& target, float& targetValue)
{
	const std::string variableName[] = { "Scum" };

	const size_t nodesSize = nodes->size();
	const size_t graphInfoSize = graphInfo.size();

	Node* temporaryTarget = nullptr;
	const NodeInfo* temporaryTargetInfo = nullptr;

	for (size_t i = 0; i < nodesSize; ++i)
	{
		temporaryTarget = (*nodes)[i];
		const uint32_t temporaryTargetId = temporaryTarget->GetId();

		temporaryTargetInfo = nullptr;

		for (size_t j = 0; j < graphInfoSize; ++j)
		{
			if (temporaryTargetId == graphInfo[j].myId)
			{
				temporaryTargetInfo = &graphInfo[j];
				break;
			}
		}

		if (temporaryTargetInfo == nullptr) continue;

		AddVariables(variableName, temporaryTargetInfo, 1);
		engine->process();
		const float outputValue = (float)outputVariable->getOutputValue();

		if (outputValue > targetValue)
		{
			target = temporaryTarget;
			targetValue = outputValue;

			std::cout << std::endl << "Target acquired: " << outputValue << "!";
		}
	}
}