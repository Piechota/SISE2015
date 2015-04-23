#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include "Globals.h"
#include "Node.h"

class Graph
{
public:
	Graph(const uint32_t depth, const uint32_t players);
	Graph(const Graph& other);
	Graph& operator=(const Graph& other);
	~Graph();

	void Generate();
	std::vector<Node*>* GetNodes();
	const std::vector<Node*>* GetConstNodes() const;
	Node* GetRoot() const;
	Node* GetNodeById(const uint32_t id) const;
	uint32_t GetDepth() const;
	uint32_t GetPlayers() const;

private:
	std::vector<Node*> nodes;
	Node* root;
	uint32_t depth;
	uint32_t players;

	static uint32_t nodeIdCounter;
};

FORCEINLINE std::vector<Node*>* Graph::GetNodes()
{
	return &nodes;
}

FORCEINLINE const std::vector<Node*>* Graph::GetConstNodes() const
{
	return &nodes;
}

FORCEINLINE Node* Graph::GetRoot() const
{
	return root;
}

FORCEINLINE Node* Graph::GetNodeById(const uint32_t id) const
{
	Node* node = nullptr;

	for (Node* const n : nodes)
	{
		if (n != nullptr)
		{
			uint32_t nid = n->GetId();
			if (nid == id)
			{
				node = n;
				break;
			}
		}
	}

	return node;
}

FORCEINLINE uint32_t Graph::GetDepth() const
{
	return depth;
}

FORCEINLINE uint32_t Graph::GetPlayers() const
{
	return players;
}

#endif