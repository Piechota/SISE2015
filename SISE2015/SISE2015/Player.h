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

	Player(const std::string& name, const Colour& color);
	Player(const Player& other);
	virtual ~Player();

	uint32_t GetId() const;
	const std::string& GetName() const;
	const Colour& GetColor() const;

	//method called to launch thought process of the pawn, returns decision
	virtual DecisionInfo ProcessAI(const std::vector<NodeInfo>& graphInfo, const Pawn* const myPawn) = 0;

protected:
    std::string name;
	uint32_t id;

private:
	Colour color;
	static uint32_t idCounter;
};

FORCEINLINE uint32_t Player::GetId() const
{
	return id;
}

FORCEINLINE const std::string& Player::GetName() const
{
	return name;
}

FORCEINLINE const Colour& Player::GetColor() const
{
	return color;
}

#endif //_PLAYER_H_