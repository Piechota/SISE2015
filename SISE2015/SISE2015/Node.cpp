#include "Node.h"

Node::Node(int id, float x, float y)
{
	this->id = id;
	positionX = x;
	positionY = y;
	this->pawn = nullptr;
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
