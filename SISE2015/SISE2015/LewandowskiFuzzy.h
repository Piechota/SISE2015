#pragma once
#include "Headers.h"

class LewandowskiFuzzy : public FuzzyPlayer
{
public:

    virtual Decision ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn) override;

    LewandowskiFuzzy(const std::string& name, const Colour& color);
    ~LewandowskiFuzzy();
};

