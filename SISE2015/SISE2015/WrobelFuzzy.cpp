#include "Headers.h"

WrobelFuzzy::WrobelFuzzy(const std::string& name, const Colour& color) : FuzzyPlayer(name, color){}
WrobelFuzzy::~WrobelFuzzy(){}
DecisionInfo WrobelFuzzy::ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn)
{
	engine->restart();

	uint32_t nodeCount = graphInfo.size();
	float minNeighborCount = (float)graphInfo.size();
	float maxNeighborCount = 0;
	for (uint32_t i = 0; i < nodeCount; ++i)
	{
		uint32_t tmpNeighborCount = graphInfo[i].neighborIds.size();
		if (tmpNeighborCount < minNeighborCount)
		{
			minNeighborCount = (float)tmpNeighborCount;
		}
		if (tmpNeighborCount > maxNeighborCount)
		{
			maxNeighborCount = (float)tmpNeighborCount;
		}
	}
	float minDistance = (float)graphInfo.size();
	float maxDistance = 0;
	for (uint32_t i = 0; i < nodeCount; ++i)
	{
		uint32_t playerCount = graphInfo[i].distanceToPlayers.size();
		for (uint32_t j = 0; j < playerCount; ++j)
		{
			uint32_t tmpDistance = graphInfo[i].distanceToPlayers[j].distance;
			if (tmpDistance < minDistance) minDistance = (float)tmpDistance;
			if (tmpDistance > maxDistance) maxDistance = (float)tmpDistance;
		}
	}

	const std::string distanceName = "input_distance";
	InputVariable* distance = new InputVariable(distanceName, minDistance, maxDistance);
	distance->addTerm(new Triangle("FAR", minDistance, minDistance, maxDistance));
	distance->addTerm(new Triangle("NEAR", minDistance, maxDistance, maxDistance));
	engine->addInputVariable(distance);

	const std::string movementName = "input_movement";
	InputVariable* movement = new InputVariable(movementName, minNeighborCount, maxNeighborCount);
	movement->addTerm(new Triangle("RESTRICTED", minNeighborCount, minNeighborCount, maxNeighborCount));
	movement->addTerm(new Triangle("FREE", minNeighborCount, maxNeighborCount, maxNeighborCount));
	engine->addInputVariable(movement);

	const std::string dangerName = "output_danger";
	OutputVariable* danger = new OutputVariable(dangerName, 0.0f, 1.0f);
	danger->addTerm(new Triangle("LOW", 0.0f, 0.0f, 0.5f));
	danger->addTerm(new Triangle("MEDIUM", 0.0f, 0.5f, 1.0f));
	danger->addTerm(new Triangle("HIGH", 0.0f, 1.0f, 1.0f));
	engine->addOutputVariable(danger);

	const std::string selfRulesName = "rules_selfRules";
	RuleBlock* selfRules = new RuleBlock(selfRulesName);
	selfRules->addRule(Rule::parse("if input_distance is FAR and input_movement is FREE then output_danger is LOW", engine));
	selfRules->addRule(Rule::parse("if input_distance is FAR and input_movement is RESTRICTED then output_danger is MEDIUM", engine));
	selfRules->addRule(Rule::parse("if input_distance is NEAR and input_movement is FREE then output_danger is MEDIUM", engine));
	selfRules->addRule(Rule::parse("if input_distance is NEAR and input_movement is RESTRICTED then output_danger is HIGH", engine));
	engine->addRuleBlock(selfRules);

	engine->configure("AlgebraicProduct", "AlgebraicSum", "Minimum", "Maximum", "Centroid");

	const NodeInfo* myNodeInfo = &graphInfo[myPawn->GetNode()->GetId()];

	engine->setInputValue(movementName, myNodeInfo->neighborIds.size());

	float enemyDistance = 0.0f;
	uint32_t playerCount = myNodeInfo->distanceToPlayers.size();
	for (uint32_t i = 0; i < playerCount; ++i)
	{
		if (myNodeInfo->distanceToPlayers[i].distance != 0)
		{
			enemyDistance = (float)myNodeInfo->distanceToPlayers[i].distance;
			break;
		}
	}
	engine->setInputValue(distanceName, enemyDistance);

	engine->process();

	float result = (float)engine->getOutputValue("output_danger");

	float decisivePoint = 0.55f;
	Decision dec = Decision();
	if (result >= decisivePoint)
	{
		dec.type = Decision::Type::MOVE;
	}
	else{
		dec.type = Decision::Type::SHOOT;
	}

	engine->restart();


	const std::string nodeDistanceName = "input_nodeDistance";
	InputVariable* nodeDistance = new InputVariable(nodeDistanceName, minDistance, maxDistance);
	nodeDistance->addTerm(new Triangle("NEAR", minDistance, minDistance, maxDistance));
	nodeDistance->addTerm(new Triangle("FAR", minDistance, maxDistance, maxDistance));
	engine->addInputVariable(nodeDistance);

	const std::string nodeValueName = "output_nodeValue";
	float maxValue = maxDistance;
	OutputVariable* nodeValue = new OutputVariable(nodeValueName, 0.0f, maxValue);
	nodeValue->addTerm(new Triangle("BAD", -maxValue, -maxValue, maxValue));
	nodeValue->addTerm(new Triangle("GOOD", -maxValue, maxValue, maxValue));
	engine->addOutputVariable(nodeValue);

	const std::string decisionRuleBlockName = "decisionRuleBlock";
	RuleBlock* decisionRuleBlock = new RuleBlock(decisionRuleBlockName);


	if (dec.type == Decision::Type::MOVE)
	{
		decisionRuleBlock->addRule(Rule::parse("if input_nodeDistance is FAR then output_nodeValue is GOOD", engine));
		decisionRuleBlock->addRule(Rule::parse("if input_nodeDistance is NEAR then output_nodeValue is BAD", engine));
	}else{
		decisionRuleBlock->addRule(Rule::parse("if input_nodeDistance is NEAR then output_nodeValue is GOOD", engine));
		decisionRuleBlock->addRule(Rule::parse("if input_nodeDistance is FAR then output_nodeValue is BAD", engine));
	}


	engine->addRuleBlock(decisionRuleBlock);

	engine->configure("AlgebraicProduct", "AlgebraicSum", "Minimum", "Maximum", "Centroid");

	uint32_t oponentIndex = 0;
	playerCount = myNodeInfo->distanceToPlayers.size();
	for (uint32_t i = 0; i < playerCount; ++i)
	{
		if (myNodeInfo->distanceToPlayers[i].distance != 0)
		{
			oponentIndex = i;
			break;
		}
	}

	std::vector<Node*>* tmpNodes = myPawn->GetNode()->GetConnections();
	nodeCount = tmpNodes->size();
	uint32_t tmpNeibourIndex = -1;
	float* result2 = new float[nodeCount];
	for (uint32_t i = 0; i < nodeCount; ++i)
	{
		tmpNeibourIndex = (*tmpNodes)[i]->GetId();
		engine->setInputValue(nodeDistanceName, graphInfo[tmpNeibourIndex].distanceToPlayers[oponentIndex].distance);
		engine->process();
		result2[i] = (float)engine->getOutputValue(nodeValueName);
	}

	float tmpMaxValue = result2[0];
	uint32_t maxIndex = 0;
	for (uint32_t i = 1; i < nodeCount; ++i)
	{
		if (dec.type == Decision::Type::SHOOT)
		{
			if (result2[i] > tmpMaxValue)
			{
				tmpMaxValue = result2[i];
				maxIndex = i;
			}
		}else{
			if (result2[i] < tmpMaxValue)
			{
				tmpMaxValue = result2[i];
				maxIndex = i;
			}
		}
	}

	dec.target = (*tmpNodes)[maxIndex];

	return dec;
}