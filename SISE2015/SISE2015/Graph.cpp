#include "Graph.h"
#include "Node.h"

Graph::Graph(int depth, int players, float distance)
{
	this->depth = depth;
	this->players = players;
	this->distance = distance;
}

Graph::Graph(Graph& other)
{
	nodes = std::vector<Node*>(*other.GetNodes());
	root = other.GetRoot();
	depth = other.GetDepth();
	players = other.GetPlayers();
	distance = other.GetDistance();
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
	for (Node* n : nodes)
	{
		if (n != nullptr)
		{
			delete n;
			n = nullptr;
		}
	}

	root = nullptr;

	float rootPosX = 0.0f;
	float rootPosY = 0.0f;

	// initial node
	root = new Node(rootPosX, rootPosY);
	nodes.push_back(root);

	// ring-shaped nodes
	float currDistance = distance;
	float angle = 360.0f / players;

	for (int i = 0; i < depth; ++i)
	{
		// spawn nodes
		for (int j = 0; j < players; ++j) 
		{
			float nodeX = currDistance;
			float nodeY = 0.0f;

			float newNodeX = (nodeX - rootPosX) * cos(angle) - (nodeY - rootPosY) * sin(angle) + rootPosX;
			float newNodeY = (nodeX - rootPosX) * sin(angle) + (nodeY - rootPosY) * cos(angle) + rootPosY;

			Node* node = new Node(newNodeX, newNodeY);
			nodes.push_back(node);
		}

		// create connections
		for (int j = 1; j <= players; ++j) 
		{
			int index = nodes.size() - j;
			Node* n = nodes[index];

			// connect to higher indexed node OR bridge the gap between first and last node
			n->AddConnection(j != 1 ? nodes[index + 1] : nodes[index - players + 1]);

			// connect to lower indexed node OR bridge the gap between first and last node
			n->AddConnection(j != players ? nodes[index - 1] : nodes[index + players - 1]);

			// connect to a lower ring node OR to the central node (in the case of the first ring)
			index -= players;
			n->AddConnection(index > 0 ? nodes[index] : nodes[0]);
		}

		currDistance += distance;
	}
}

std::vector<Node*>* Graph::GetNodes()
{
	return &nodes;
}

Node* Graph::GetRoot()
{
	return root;
}

int Graph::GetDepth() const
{
	return depth;
}

int Graph::GetPlayers() const
{
	return players;
}

float Graph::GetDistance() const
{
	return distance;
}
