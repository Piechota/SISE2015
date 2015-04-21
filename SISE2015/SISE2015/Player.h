#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
//#include "Node.h"
class Pawn;
class Node;
class Graph;

//this is temporary, we'll need sth more complex, and not just 4 directions -> waiting for grapth

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

//TODO: swap int with some real type later on
#define GraphInfo Graph
//this depends on the structure of graph
#define DecisionInfo Decision

class Player
{
private:
	static int idCounter;
	int id;
	std::string name;

public:
	static void ResetIdIndexing();

	Player(std::string name);
	Player(const Player &other);
	~Player();

	int GetId() const;
	std::string GetName() const;

	//method called to launch thought process of the pawn, returns decision
	virtual DecisionInfo ProcessAI(GraphInfo* grapthInfo, Pawn* myPawn) = 0;
};

#endif //_PLAYER_H_