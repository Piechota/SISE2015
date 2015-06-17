#include "Graph.h"
#include <stdio.h>
#include <math.h>

Graph::Graph(const uint32_t depth, const uint32_t players)
{
	this->depth = depth;
	this->players = players;
	this->nodeIdCounter = 0;
}

Graph::Graph(const Graph& other)
{
	nodes = std::vector<Node*>(*other.GetConstNodes());
	root = other.GetRoot();
	depth = other.GetDepth();
	players = other.GetPlayers();
	this->nodeIdCounter = other.nodeIdCounter;
}

Graph& Graph::operator=(const Graph& other)
{
	if (this != &other)
	{
		nodes = std::vector<Node*>(*other.GetConstNodes());
		root = other.GetRoot();
		depth = other.GetDepth();
		players = other.GetPlayers();
		this->nodeIdCounter = other.nodeIdCounter;
	}

	return *this;
}

Graph::~Graph()
{
	for (Node* n : nodes)
	{
		if (n != nullptr)
		{
			delete n;
			n = nullptr;
		}
	}

	root = nullptr;
}


uint32_t Graph::GetNodeCount() const
{
	return this->nodeIdCounter;
}

void Graph::Generate()
{
	Graph::nodeIdCounter = 0;

	for (Node* n : nodes)
	{
		if (n != nullptr)
		{
			delete n;
			n = nullptr;
		}
	}

	root = nullptr;

	static const uint32_t distance = (uint32_t)(screen_height / (depth * 2.5));

	const int32_t rootPosX = screen_width / 2;
	const int32_t rootPosY = screen_height / 2;

	// initial node
	root = new Node(Graph::nodeIdCounter++, rootPosX, rootPosY);
	nodes.push_back(root);

	// ring-shaped nodes
	uint32_t currDistance = distance;
	float angle = 360.0f / players;
	angle *= 0.01745f;

	for (size_t i = 0; i < depth; ++i)
	{
		int32_t nodeX = rootPosX + currDistance;
		int32_t nodeY = rootPosY;

		// spawn nodes
		for (size_t j = 0; j < players; ++j)
		{
			int32_t newNodeX = (int32_t)((nodeX - rootPosX) * cos(angle) - (nodeY - rootPosY) * sin(angle) + rootPosX);
			int32_t newNodeY = (int32_t)((nodeX - rootPosX) * sin(angle) + (nodeY - rootPosY) * cos(angle) + rootPosY);
			//float newNodeX = rootPosX + (nodeX - rootPosX)*cos(angle) - (nodeY - rootPosY)*sin(angle);
			//float newNodeY = rootPosY + (nodeX - rootPosX)*sin(angle) + (nodeY - rootPosY)*cos(angle);

			nodeX = newNodeX;
			nodeY = newNodeY;

			Node* const node = new Node(this->nodeIdCounter++, newNodeX, newNodeY);
			nodes.push_back(node);
		}

		// create connections
		for (size_t j = 1; j <= players; ++j)
		{
			const size_t index = nodes.size() - j;
			Node* const n = nodes[index];

			// connect to higher indexed node OR bridge the gap between first and last node
			n->AddConnection(j != 1 ? nodes[index + 1] : nodes[index - players + 1]);

			// connect to lower indexed node OR bridge the gap between first and last node
			n->AddConnection(j != players ? nodes[index - 1] : nodes[index + players - 1]);

			// connect to a lower ring node OR to the central node (in the case of the first ring)
			//index -= players;
			//n->AddConnection(index > 0 ? nodes[index] : nodes[0]);
			n->AddConnection(index > players ? nodes[index - players] : nodes[0]);

			if (index > players) nodes[index - players]->AddConnection(n);
			else nodes[0]->AddConnection(n);
		}

		currDistance += distance;
	}
}


std::vector<NodeInfo> Graph::GenerateNodesForLogic(uint32_t* playerNodeIds, uint32_t playerCount)
{
	uint32_t nodeCount = this->GetNodeCount();
	std::vector<Node*>* tmpNodes;
	std::vector<NodeInfo> resultInfos;
	std::vector<Node*>* tmpNeighbors = nullptr;

	tmpNodes = this->GetNodes();

	for (uint32_t i = 0; i < nodeCount; ++i)
	{
		resultInfos.push_back(NodeInfo((*tmpNodes)[i]->GetId()));
		tmpNeighbors = (*tmpNodes)[i]->GetConnections();
		uint32_t neightborCount = tmpNeighbors->size();
		for (uint32_t j = 0; j < neightborCount; ++j)
		{
			resultInfos[i].neighborIds.push_back((*tmpNeighbors)[j]->GetId());
		}
		for (uint32_t j = 0; j < playerCount; ++j)
		{
			resultInfos[i].distanceToPlayers.push_back(-1);
		}
	}

	bool* visited = new bool[nodeCount];
	std::queue<Node*> toVisit;

	uint32_t tmpPlayerNodeId = -1;
	for (uint32_t playerIndex = 0; playerIndex < playerCount; tmpPlayerNodeId = ++playerIndex)
	{
		for (uint32_t i = 0; i < nodeCount; ++i)
		{
			visited[i] = false;
			resultInfos[i].distanceToPlayers[playerIndex] = -1;
		}
		uint32_t startingIndex = playerNodeIds[playerIndex];
		
		Node* currentNode;
		
		resultInfos[startingIndex].distanceToPlayers[playerIndex] = 0;
		toVisit.push((*tmpNodes)[startingIndex]);
		visited[startingIndex] = true;

		while (!toVisit.empty())
		{
			currentNode = toVisit.front();
			toVisit.pop();

			uint32_t currentId = currentNode->GetId();
			uint32_t currentDistance = resultInfos[currentId].distanceToPlayers[playerIndex];
			tmpNeighbors = currentNode->GetConnections();
			uint32_t neighborCount = tmpNeighbors->size();
			for (uint32_t i = 0; i < neighborCount; ++i)
			{
				uint32_t tmpId = (*tmpNeighbors)[i]->GetId();
				//resultInfos[currentId].neighborIds.push_back(tmpId);
				if (!visited[tmpId] || resultInfos[tmpId].distanceToPlayers[playerIndex] > currentDistance + 1 || resultInfos[tmpId].distanceToPlayers[playerIndex] == -1)
				{
					resultInfos[tmpId].distanceToPlayers[playerIndex] = currentDistance + 1;
				}

				if (!visited[tmpId])
				{
					visited[tmpId] = true;
					toVisit.push((*tmpNeighbors)[i]);
				}
			}
		}
	}

	delete[nodeCount] visited;

	return resultInfos;
}