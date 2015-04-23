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

void GraphRenderer::RenderGraph(const Graph* const graph)
{
	const std::vector<Node*>* const nodes = graph->GetConstNodes();

	for (const Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			const std::vector<Node*>* const connections = n->GetConstConnections();
			const int32_t nx = n->GetPositionX();
			const int32_t ny = n->GetPositionY();

			for (const Node* const c : *connections)
			{
				if (c != nullptr)
				{
					const int32_t cx = c->GetPositionX();
					const int32_t cy = c->GetPositionY();

					DrawLine(Colors::red, nx, ny, cx, cy);
				}
			}
		}
	}

	for (const Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			const int32_t nx = n->GetPositionX();
			const int32_t ny = n->GetPositionY();

			DrawCircle(Colors::green, Colors::white, nx, ny, 20, 5);

			const Pawn* const pawn = n->GetPawn();

			if (pawn != nullptr)
			{
				DrawCircle(pawn->color, nx, ny, 10);
			}
		}
	}
}