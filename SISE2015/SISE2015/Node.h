#ifndef _NODE_H_
#define _NODE_H_

#include "Headers.h"

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

#endif