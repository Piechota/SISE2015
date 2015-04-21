#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Headers.h"

class Graph
{
public:
	Graph(int depth, int players, float distance);
	Graph(Graph& other);
	~Graph();

	void Generate();
	std::vector<Node*>* GetNodes();
	Node* GetRoot();
	Node* GetNodeById(const int id);
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

#endif