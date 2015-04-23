#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Headers.h"

struct Decision
{
	Node* target;

	enum class Type : uint8_t
	{		
		MOVE = 0,
		SHOOT,
		SUICIDE,

		COUNT
	};
	Type type;
};

#define GraphInfo Graph
#define DecisionInfo Decision

class Player
{
public:
	static void ResetIdIndexing();

	Player(std::string name);
	Player(const Player& other);
	~Player();

	uint32_t GetId() const;
	std::string GetName() const;

	//method called to launch thought process of the pawn, returns decision
	virtual DecisionInfo ProcessAI(GraphInfo* const grapthInfo, Pawn* const myPawn) = 0;

protected:
    std::string name;

private:
	static uint32_t idCounter;
    uint32_t id;
};

#endif //_PLAYER_H_