#include "Graph.h"

uint32_t Graph::nodeIdCounter = 0;

Graph::Graph(const uint32_t depth, const uint32_t players)
{
	this->depth = depth;
	this->players = players;
}

Graph::Graph(const Graph& other)
{
	nodes = std::vector<Node*>(*other.GetConstNodes());
	root = other.GetRoot();
	depth = other.GetDepth();
	players = other.GetPlayers();
}

Graph& Graph::operator=(const Graph& other)
{
	if (this != &other)
	{
		nodes = std::vector<Node*>(*other.GetConstNodes());
		root = other.GetRoot();
		depth = other.GetDepth();
		players = other.GetPlayers();
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

			Node* const node = new Node(Graph::nodeIdCounter++, newNodeX, newNodeY);
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
