#pragma once
#include <vector>
#include <exception>

class Node
{	
public:
	std::vector<Node>* GetConnections()
	{
		throw 0;
	}

	Node(const Node& source)
	{
		//copy node
		throw 0;
	}

	Node();
	~Node();
};

