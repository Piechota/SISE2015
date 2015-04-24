#include <vector>
#include "Globals.h"
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
	const size_t size = nodes->size();

	int32_t* RESTRICT const x = new int32_t[size];
	int32_t* RESTRICT const y = new int32_t[size];
	size_t i = 0;

	static const uint32_t nodeCircleRadius = (uint32_t)(screen_height / 16);
	static const uint32_t nodeBorderSize = (uint32_t)(nodeCircleRadius / 4);
	static const uint32_t pawnCircleRadius = (uint32_t)(nodeCircleRadius / 2);

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

					DrawLine(Colors::black, nx, ny, cx, cy);
				}
			}
		}
	}

	for (const Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			x[i] = n->GetPositionX();
			y[i] = n->GetPositionY();
			i++;
		}
	}

	DrawCircle(Colors::green, Colors::white, x, y, nodeCircleRadius, nodeBorderSize, size);

	for (const Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			const Pawn* const pawn = n->GetPawn();

			if (pawn != nullptr)
			{
				const int32_t nx = n->GetPositionX();
				const int32_t ny = n->GetPositionY();

				DrawCircle(pawn->color, nx, ny, pawnCircleRadius);
			}
		}
	}
}