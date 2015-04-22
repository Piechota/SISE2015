#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include "Globals.h"
#include "Node.h"

class Graph
{
public:
	Graph(size_t depth, size_t players, float distance);
	Graph(Graph& other);
	~Graph();

	void Generate();
	std::vector<Node*>* GetNodes();
	Node* GetRoot() const;
	Node* GetNodeById(const size_t id) const;
	size_t GetDepth() const;
	size_t GetPlayers() const;
	float GetDistance() const;

private:
	std::vector<Node*> nodes;
	Node* root;
	size_t depth;
	size_t players;
	float distance;

	static size_t nodeIdCounter;
};

FORCEINLINE std::vector<Node*>* Graph::GetNodes()
{
	return &nodes;
}

FORCEINLINE Node* Graph::GetRoot() const
{
	return root;
}

FORCEINLINE Node* Graph::GetNodeById(const size_t id) const
{
	Node* node = nullptr;

	for (Node* const n : nodes)
	{
		if (n != nullptr)
		{
			size_t nid = n->GetId();
			if (nid == id)
			{
				node = n;
				break;
			}
		}
	}

	return node;
}

FORCEINLINE size_t Graph::GetDepth() const
{
	return depth;
}

FORCEINLINE size_t Graph::GetPlayers() const
{
	return players;
}

FORCEINLINE float Graph::GetDistance() const
{
	return distance;
}

#endif