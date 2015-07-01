#include "LewandowskiFuzzy.h"

LewandowskiFuzzy::LewandowskiFuzzy(const std::string& name, const Colour& color) :FuzzyPlayer(name, color)
{
}

LewandowskiFuzzy::~LewandowskiFuzzy()
{
}

Decision LewandowskiFuzzy::ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn)
{
    engine->restart();

    InputVariable* input = new InputVariable();
    input->setName("DistanceToEnemy");
    input->setRange(0.0, 8.0);
    input->addTerm(new Trapezoid("CLOSE", 0.0, 0.0, 1.0, 1.0));
    input->addTerm(new Trapezoid("NOTCLOSE", 1.0, 1.0, 8.0, 8.0));
    engine->addInputVariable(input);

    OutputVariable* output = new OutputVariable();
    output->setName("Decision");
    output->setRange(0.0, 1.0);
    output->addTerm(new Triangle("ATTACK", 0.0, 0.1, 0.2));
    output->addTerm(new Triangle("MOVE", 0.2, 0.8, 1.0));
    engine->addOutputVariable(output);

    RuleBlock* rule = new RuleBlock;
    rule->addRule(Rule::parse("if DistanceToEnemy is CLOSE then Decision is ATTACK", engine));
    rule->addRule(Rule::parse("if DistanceToEnemy is NOTCLOSE then Decision is MOVE", engine));
    engine->addRuleBlock(rule);
    engine->configure("", "", "Minimum", "Maximum", "Centroid");

    std::string status;
    if (!engine->isReady(&status))
    {
        printf("Engine not ready. \nThe following errors were encountered:\n" + *status.c_str());
    }


    int playersCount = graphInfo.at(0).distanceToPlayers.size() - 1;
    std::vector<uint32_t> myNeighboursID = graphInfo.at(myPawn->GetNode()->GetId()).neighborIds;
    int neighboursCount = myNeighboursID.size();
    std::vector<double> neighbours(neighboursCount);


    for (int i = 0; i < neighboursCount; ++i)
    {
        std::vector<DistanceToPlayer> tmp;
        for (auto j = 0; j < graphInfo.at(myNeighboursID.at(i)).distanceToPlayers.size(); ++j)
        {
            if (graphInfo.at(myNeighboursID.at(i)).distanceToPlayers.at(j).playerID != id)
            {
                tmp.push_back(graphInfo.at(myNeighboursID.at(i)).distanceToPlayers.at(j));
            }
        }

        DistanceToPlayer closestPlayer =
            *std::min_element(
                tmp.begin(),
                tmp.end(),
                [](DistanceToPlayer d1, DistanceToPlayer d2)
                {
                    return d1.distance < d2.distance;
                });


        engine->setInputValue("DistanceToEnemy", closestPlayer.distance);
        engine->process();
        neighbours[i] = engine->getOutputValue("Decision");
    }

    std::vector<int> attackIndx;
    std::vector<int> moveIndx;

    double treshold = 0.185;

    for (int i = 0; i < neighboursCount; ++i)
    {
        if (neighbours[i] <= treshold)
        {
            attackIndx.push_back(i);
        }
        else
        {
            moveIndx.push_back(i);
        }
    }
    Decision d;

    if (attackIndx.size() > 0)
    {
        d.type = Decision::Type::SHOOT;
        int targetID =
            graphInfo.at(myNeighboursID.at(attackIndx.at(rand() % attackIndx.size()))).myId;

        auto conn = myPawn->GetNode()->GetConnections();

        for (int i = 0; i < conn->size(); ++i)
        {
            if (conn->at(i)->GetId() == targetID)
            {
                d.target = conn->at(i);
            }
        }
    }
    else
    {
        d.type = Decision::Type::MOVE;
        int targetID = graphInfo.at(myNeighboursID.at(moveIndx.at(rand() % moveIndx.size()))).myId;

        auto conn = myPawn->GetNode()->GetConnections();

        for (int i = 0; i < conn->size(); ++i)
        {
            if (conn->at(i)->GetId() == targetID)
            {
                d.target = conn->at(i);
            }
        }
    }

    engine->removeInputVariable("DistanceToEnemy");
    engine->removeOutputVariable("Decision");
    engine->removeRuleBlock(0);
    return d;
}
