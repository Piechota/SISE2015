#include <vector>
#include "Globals.h"
#include "GraphRenderer.h"
#include "Graph.h"
#include "Node.h"
#include "Renderer.h"
#include "Colour.h"
#include "Pawn.h"

GraphRenderer::GraphRenderer()
{
}

GraphRenderer::~GraphRenderer()
{
}

void GraphRenderer::RenderBackground() 
{
	SDL_SetRenderDrawColor(renderer, Colours::background.r, Colours::background.g, Colours::background.b, SDL_ALPHA_OPAQUE);
}

void GraphRenderer::RenderGraph(const Graph* const graph) 
{
	SDL_RenderClear(renderer);

	const std::vector<Node*>* const nodes = graph->GetConstNodes();
	const size_t size = nodes->size();

	int32_t* RESTRICT const x = new int32_t[size];
	int32_t* RESTRICT const y = new int32_t[size];
	size_t i = 0;

	static const uint32_t nodeCircleRadius = (uint32_t)(screen_height / 16);
	static const uint32_t nodeBorderSize = (uint32_t)(nodeCircleRadius / 4);
	static const uint32_t pawnCircleRadius = (uint32_t)(nodeCircleRadius / 2);

	// draw graph lines
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

					DrawLine(Colours::black, nx, ny, cx, cy);
				}
			}
		}
	}

	// draw graph nodes
	for (const Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			x[i] = n->GetPositionX();
			y[i] = n->GetPositionY();
			i++;
		}
	}

	DrawCircle(Colours::nodeInner, Colours::nodeOuter, x, y, nodeCircleRadius, nodeBorderSize, size);

	const Pawn* const currentPawn = game->GetCurrentPawn();

	// draw pawns
	for (const Node* const n : *nodes)
	{
		if (n != nullptr)
		{
			const Pawn* const pawn = n->GetPawn();

			if (pawn != nullptr)
			{
				const int32_t nx = n->GetPositionX();
				const int32_t ny = n->GetPositionY();

				if (currentPawn == pawn) {
					// pawn->color
					DrawCircle(Colours::pawnActive, nx, ny, pawnCircleRadius);
				}
				else {
					DrawCircle(Colours::pawn, nx, ny, pawnCircleRadius);
				}
			}
		}
	}

	SDL_RenderPresent(renderer);
}