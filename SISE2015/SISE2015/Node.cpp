#include "Node.h"

Node::Node(int id, float x, float y)
{
	this->id = id;
	positionX = x;
	positionY = y;
}

Node::Node(Node& other)
{
	id = other.GetId();
	neighbors = std::vector<Node*>(*other.GetConnections());
	positionX = other.GetPositionX();
	positionY = other.GetPositionY();
	pawn = other.GetPawn();
}

Node::~Node()
{
}

int Node::GetId() const
{
	return id;
}

std::vector<Node*>* Node::GetConnections()
{
	return &neighbors;
}

void Node::AddConnection(Node* const node)
{
	if (node != nullptr) neighbors.push_back(node);
}

bool Node::IsConnectedTo(Node* const node) const
{
	if (node == nullptr) return false;

	for (Node* const n : neighbors)
	{
		if (n == node) return true;
	}
	
	return false;
}

float Node::GetPositionX() const
{
	return positionX;
}

float Node::GetPositionY() const
{
	return positionY;
}

void Node::SetPawn(Pawn* const pawn)
{
	this->pawn = pawn;
}

Pawn* Node::GetPawn() const
{
	return pawn;
}
