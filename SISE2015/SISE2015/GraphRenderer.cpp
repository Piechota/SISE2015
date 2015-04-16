#include <vector>
#include "GraphRenderer.h"
#include "Graph.h"
#include "Node.h"
#include "Renderer.h"
#include "Color.h"

GraphRenderer::GraphRenderer()
{
}

GraphRenderer::~GraphRenderer()
{
}

void GraphRenderer::RenderGraph(Graph* const graph)
{
	std::vector<Node*>* const nodes = graph->GetNodes();

	for (Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			std::vector<Node*>* const connections = n->GetConnections();
			float nx = n->getPositionX();
			float ny = n->getPositionY();

			for (Node* const c : *connections)
			{
				if (c != nullptr)
				{
					float cx = c->getPositionX();
					float cy = c->getPositionY();

					DrawLine(Colors::red, nx, ny, cx, cy);
				}
			}
		}
	}

	for (Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			float nx = n->getPositionX();
			float ny = n->getPositionY();

			DrawCircle(Colors::green, Colors::white, nx, ny, 50.0f, 5.0f);
		}
	}
}