#include <vector>
#include "GraphRenderer.h"
#include "Graph.h"
#include "Node.h"
#include "Renderer.h"
#include "Color.h"
#include "Pawn.h"

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

	for (Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			float nx = n->GetPositionX();
			float ny = n->GetPositionY();

			DrawCircle(Colors::green, Colors::white, nx, ny, 20.0f, 5.0f);

			Pawn* const pawn = n->GetPawn();

			if (pawn != nullptr)
			{
				DrawCircle(pawn->color, nx, ny, 10.0f);
			}
		}
	}
}