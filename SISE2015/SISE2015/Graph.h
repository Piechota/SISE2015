#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <queue>
#include "Globals.h"
#include "Node.h"

struct DistanceToPlayer
{
	DistanceToPlayer(uint32_t _distance, uint32_t _playerID) :
		distance(_distance),
		playerID(_playerID)
	{
		
	}
	uint32_t distance;
	uint32_t playerID;
};

struct NodeInfo
{
public:
	NodeInfo(uint32_t myId)
	{
		this->myId = myId;
	}
	uint32_t myId;
	std::vector<DistanceToPlayer> distanceToPlayers;
	std::vector<uint32_t> neighborIds;
};

class Graph
{
public:
	Graph(const uint32_t depth, const uint32_t players);
	Graph(const Graph& other);
	Graph& operator=(const Graph& other);
	~Graph();

	void Generate();
	std::vector<Node*>* GetNodes();
	const std::vector<Node*>* GetNodes() const;
	Node* GetRoot() const;
	Node* GetNodeById(const uint32_t id) const;
	uint32_t GetDepth() const;
	uint32_t GetPlayers() const;
	uint32_t GetNodeCount() const;
	std::vector<NodeInfo> GenerateNodesForLogic(const uint32_t* const playerNodeIds, const uint32_t playerCount) const;

private:
	std::vector<Node*> nodes;
	Node* root;
	uint32_t depth;
	uint32_t players;
	uint32_t nodeIdCounter;
};

FORCEINLINE std::vector<Node*>* Graph::GetNodes()
{
	return &nodes;
}

FORCEINLINE const std::vector<Node*>* Graph::GetNodes() const
{
	return &nodes;
}

FORCEINLINE uint32_t Graph::GetNodeCount() const
{
	return nodeIdCounter;
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
			const uint32_t nid = n->GetId();
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