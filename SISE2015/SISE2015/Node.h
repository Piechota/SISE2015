#ifndef _NODE_H_
#define _NODE_H_

#include <vector>

class Node
{	
public:
	Node(float x, float y);
	Node(Node& other);
	~Node();

	std::vector<Node*>* GetConnections();
	void AddConnection(Node* const node);
	bool IsConnectedTo(Node* const node) const;
	float getPositionX() const;
	float getPositionY() const;

private:
	std::vector<Node*> neighbors;
	float positionX;
	float positionY;
};

#endif