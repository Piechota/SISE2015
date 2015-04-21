#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include "Globals.h"
#include "Node.h"

class Graph
{
public:
	Graph(int depth, int players, float distance);
	Graph(Graph& other);
	~Graph();

	void Generate();
	std::vector<Node*>* GetNodes();
	Node* GetRoot() const;
	Node* GetNodeById(const int id) const;
	int GetDepth() const;
	int GetPlayers() const;
	float GetDistance() const;

private:
	std::vector<Node*> nodes;
	Node* root;
	int depth;
	int players;
	float distance;

	static int nodeIdCounter;
};

FORCEINLINE std::vector<Node*>* Graph::GetNodes()
{
	return &nodes;
}

FORCEINLINE Node* Graph::GetRoot() const
{
	return root;
}

FORCEINLINE Node* Graph::GetNodeById(const int id) const
{
	Node* node = nullptr;

	for (Node* const n : nodes)
	{
		if (n != nullptr)
		{
			int nid = n->GetId();
			if (nid == id)
			{
				node = n;
				break;
			}
		}
	}

	return node;
}

FORCEINLINE int Graph::GetDepth() const
{
	return depth;
}

FORCEINLINE int Graph::GetPlayers() const
{
	return players;
}

FORCEINLINE float Graph::GetDistance() const
{
	return distance;
}

#endif