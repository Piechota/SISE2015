#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Headers.h"

struct Decision
{
	enum Type
	{		
		MOVE = 0,
		SHOOT,
		SUICIDE,

		COUNT
	};
	Type type;

	Node* target;
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

	int GetId() const;
	std::string GetName() const;

	//method called to launch thought process of the pawn, returns decision
	virtual DecisionInfo ProcessAI(GraphInfo* const grapthInfo, Pawn* const myPawn) = 0;

protected:
    std::string name;

private:
    static int idCounter;
    int id;
};

#endif //_PLAYER_H_