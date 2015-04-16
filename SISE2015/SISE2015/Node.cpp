#include "Node.h"

Node::Node(float x, float y)
{
	positionX = x;
	positionY = y;
}

Node::Node(Node& other)
{
	neighbors = std::vector<Node*>(*other.GetConnections());
	positionX = other.getPositionX();
	positionY = other.getPositionY();
}

Node::~Node()
{
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

float Node::getPositionX() const
{
	return positionX;
}

float Node::getPositionY() const
{
	return positionY;
}
