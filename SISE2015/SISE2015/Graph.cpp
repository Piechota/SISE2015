#include "Graph.h"
#include "Node.h"
#include "Globals.h"

int Graph::nodeIdCounter = 0;

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

	float rootPosX = screen_width / 2.0f;
	float rootPosY = screen_height / 2.0f;

	// initial node
	root = new Node(Graph::nodeIdCounter++, rootPosX, rootPosY);
	nodes.push_back(root);

	// ring-shaped nodes
	float currDistance = distance;
	float angle = 360.0f / players;
	angle *= 0.01745f;

	for (int i = 0; i < depth; ++i)
	{
		float nodeX = rootPosX + currDistance;
		float nodeY = rootPosY;

		// spawn nodes
		for (int j = 0; j < players; ++j) 
		{
			float newNodeX = (nodeX - rootPosX) * cos(angle) - (nodeY - rootPosY) * sin(angle) + rootPosX;
			float newNodeY = (nodeX - rootPosX) * sin(angle) + (nodeY - rootPosY) * cos(angle) + rootPosY;
			//float newNodeX = rootPosX + (nodeX - rootPosX)*cos(angle) - (nodeY - rootPosY)*sin(angle);
			//float newNodeY = rootPosY + (nodeX - rootPosX)*sin(angle) + (nodeY - rootPosY)*cos(angle);

			nodeX = newNodeX;
			nodeY = newNodeY;

			Node* node = new Node(Graph::nodeIdCounter++, newNodeX, newNodeY);
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

Node* Graph::GetNodeById(const int id)
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
