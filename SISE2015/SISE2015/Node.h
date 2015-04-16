#ifndef _NODE_H_
#define _NODE_H_

#include <vector>

class Pawn;

class Node
{	
public:
	Node(int id, float x, float y);
	Node(Node& other);
	~Node();

	int GetId() const;
	std::vector<Node*>* GetConnections();
	void AddConnection(Node* const node);
	bool IsConnectedTo(Node* const node) const;
	float GetPositionX() const;
	float GetPositionY() const;
	void SetPawn(Pawn* const pawn);
	Pawn* GetPawn() const;

private:
	int id;
	std::vector<Node*> neighbors;
	float positionX;
	float positionY;
	Pawn* pawn;
};

#endif