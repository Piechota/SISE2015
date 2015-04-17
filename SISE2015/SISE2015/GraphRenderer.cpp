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
			float nx = n->GetPositionX();
			float ny = n->GetPositionY();

			for (Node* const c : *connections)
			{
				if (c != nullptr)
				{
					float cx = c->GetPositionX();
					float cy = c->GetPositionY();

					DrawLine(Colors::red, nx, ny, cx, cy);
				}
			}
		}
	}

	int nodeCount = nodes->size();
	for (int i = 0; i < nodeCount; ++i)
	{
		if ((*nodes)[i] != nullptr)
		{
			float nx = (*nodes)[i]->GetPositionX();
			float ny = (*nodes)[i]->GetPositionY();

			DrawCircle(Colors::green, Colors::white, nx, ny, 20.0f, 5.0f);

			if ((*nodes)[i]->GetPawn() != nullptr)
			{
				DrawCircle(Colors::blue, nx, ny, 10.0f);
			}
		}
	}
	/*for (Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			
			float nx = n->GetPositionX();
			float ny = n->GetPositionY();

			DrawCircle(Colors::green, Colors::white, nx, ny, 20.0f, 5.0f);
		}
	}*/
}