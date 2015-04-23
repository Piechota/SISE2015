#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "Globals.h"

class Pawn;

class Node
{	
public:
	Node(const uint32_t id, const int32_t x, const int32_t y);
	Node(const Node& other);
	Node& operator=(const Node& other);
	Node(Node&& other);
	Node& operator=(Node&& other);
	~Node();

	uint32_t GetId() const;
	std::vector<Node*>* GetConnections();
	const std::vector<Node*>* GetConstConnections() const;
	void AddConnection(Node* const node);
	bool IsConnectedTo(const Node* const node) const;
	int32_t GetPositionX() const;
	int32_t GetPositionY() const;
	void SetPawn(Pawn* const pawn);
	Pawn* GetPawn() const;

private:
	std::vector<Node*> neighbors;
	Pawn* pawn;
	uint32_t id;
	int32_t positionX;
	int32_t positionY;
};

FORCEINLINE uint32_t Node::GetId() const
{
	return id;
}

FORCEINLINE std::vector<Node*>* Node::GetConnections()
{
	return &neighbors;
}

FORCEINLINE const std::vector<Node*>* Node::GetConstConnections() const
{
	return &neighbors;
}

FORCEINLINE void Node::AddConnection(Node* const node)
{
	if (node != nullptr) neighbors.push_back(node);
}

FORCEINLINE bool Node::IsConnectedTo(const Node* const node) const
{
	if (node == nullptr) return false;

	for (const Node* const n : neighbors)
	{
		if (n == node) return true;
	}

	return false;
}

FORCEINLINE int32_t Node::GetPositionX() const
{
	return positionX;
}

FORCEINLINE int32_t Node::GetPositionY() const
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