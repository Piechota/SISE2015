#include "Node.h"

Node::Node(const uint32_t id, const int32_t x, const int32_t y)
{
	this->id = id;
	positionX = x;
	positionY = y;
	pawn = nullptr;
}

Node::Node(const Node& other)
{
	id = other.GetId();
	neighbors = std::vector<Node*>(*other.GetConstConnections());
	positionX = other.GetPositionX();
	positionY = other.GetPositionY();
	pawn = other.GetPawn();
}

Node& Node::operator=(const Node& other)
{
	if (this != &other)
	{
		id = other.GetId();
		neighbors = std::vector<Node*>(*other.GetConstConnections());
		positionX = other.GetPositionX();
		positionY = other.GetPositionY();
		pawn = other.GetPawn();
	}

	return *this;
}

Node::Node(Node&& other)
{
	id = other.GetId();
	neighbors = std::move(*other.GetConnections());
	positionX = other.GetPositionX();
	positionY = other.GetPositionY();
	pawn = other.GetPawn();

	other.SetPawn(nullptr);
	other.neighbors.clear();
}

Node& Node::operator=(Node&& other)
{
	if (this != &other)
	{
		id = other.GetId();
		neighbors = std::move(*other.GetConnections());
		positionX = other.GetPositionX();
		positionY = other.GetPositionY();
		pawn = other.GetPawn();

		other.SetPawn(nullptr);
		other.neighbors.clear();
	}

	return *this;
}

Node::~Node()
{
}
