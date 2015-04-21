#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "Globals.h"

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

FORCEINLINE int Node::GetId() const
{
	return id;
}

FORCEINLINE std::vector<Node*>* Node::GetConnections()
{
	return &neighbors;
}

FORCEINLINE void Node::AddConnection(Node* const node)
{
	if (node != nullptr) neighbors.push_back(node);
}

FORCEINLINE bool Node::IsConnectedTo(Node* const node) const
{
	if (node == nullptr) return false;

	for (Node* const n : neighbors)
	{
		if (n == node) return true;
	}

	return false;
}

FORCEINLINE float Node::GetPositionX() const
{
	return positionX;
}

FORCEINLINE float Node::GetPositionY() const
{
	return positionY;
}

FORCEINLINE void Node::SetPawn(Pawn* const pawn)
{
	this->pawn = pawn;
}

FORCEINLINE Pawn* Node::GetPawn() const
{
	return pawn;
}

#endif