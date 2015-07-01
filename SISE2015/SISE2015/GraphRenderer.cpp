#include <vector>
#include <stdio.h>
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

	const std::vector<Node*>* const nodes = graph->GetNodes();
	const size_t size = nodes->size();
	const uint32_t depth = graph->GetDepth();
	const uint32_t players = graph->GetPlayers();

	static const uint32_t distance = (uint32_t)(screen_height / (depth * 2.5));
	static const int32_t rootPosX = screen_width / 2;
	static const int32_t rootPosY = screen_height / 2;

	uint32_t currDistance = distance;
	float angle = 360.0f / (float)players;
	angle *= 0.01745f;

	uint32_t nodeId = 1; // skip root node

	const float offset = sin((float)currentTime / 300.0f) * 100.0f;

	for (size_t i = 0; i < depth; ++i)
	{
		int32_t nodeX = rootPosX + currDistance;
		int32_t nodeY = rootPosY + offset * (i + 1);

		for (size_t j = 0; j < players; ++j)
		{
			int32_t newNodeX = (int32_t)((nodeX - rootPosX) * cos(angle) - (nodeY - rootPosY) * sin(angle) + rootPosX);
			int32_t newNodeY = (int32_t)((nodeX - rootPosX) * sin(angle) + (nodeY - rootPosY) * cos(angle) + rootPosY);

			nodeX = newNodeX;
			nodeY = newNodeY;

			(*nodes)[nodeId]->SetPositionX(newNodeX);
			(*nodes)[nodeId]->SetPositionY(newNodeY);

			nodeId++;
		}

		currDistance += distance;
	}

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
			const std::vector<Node*>* const connections = n->GetConnections();
			const int32_t nx = n->GetPositionX();
			const int32_t ny = n->GetPositionY();

			x[i] = nx;
			y[i] = ny;
			i++;

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
