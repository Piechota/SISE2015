#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <exception>
#include <SDL.h>

#include "DataStructures.h"
#include "Globals.h"

#include "Pawn.h"
#include "Player.h"
#include "ExamplePlayer.h"
#include "GameController.h"

#include "Graph.h"
#include "Renderer.h"
#include "GraphRenderer.h"

bool Init(const int& w, const int& h)
{
	screen_width = w;
	screen_height = h;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("SISE2015", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
void Close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
int main(int argc, char* args[])
{
	if (!Init(screen_width, screen_height))
		return 1;

	bool run = true;
	SDL_Event event;

	int testAmount = 4;
	Player** pawns = new Player*[testAmount];
	for (int i = 0; i < testAmount; ++i)
	{
		pawns[i] = new ExamplePlayer();
	}

	int tmpRadius = 10;
	Color** colors = new Color*[testAmount];
	int* posX = new int[testAmount];
	int* posY = new int[testAmount];
	for (int i = 0; i < testAmount; ++i)
	{
		colors[i] = new Color(50 * i, 100, 255 - 50 * i);
		posX[i] = 300;
		posY[i] = 300;
	}
	int stepValue = 50;
	int lastTime = time(NULL);
	int currentTime = lastTime;
	Decision tmpDecision;

	Graph* graph = new Graph(2, 6, 100.0f);
	graph->Generate();

	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				run = false;
		}

		SDL_SetRenderDrawColor(renderer, Colors::black.r, Colors::black.g, Colors::black.b, 0xFF);
		SDL_RenderClear(renderer);

		if (lastTime != (currentTime = time(NULL)))
		{
			for (int i = 0; i < testAmount; ++i)
			{
				tmpDecision = pawns[i]->ProcessAI(currentTime);

				switch (tmpDecision)
				{
				case Decision::DO_NTH:
					break;
				case Decision::MOVE_UP:
					if (posY[i] < screen_height - stepValue)
						posY[i] += stepValue;
					break;
				case Decision::MOVE_DOWN:
					if (posY[i] > stepValue)
						posY[i] -= stepValue;
					break;
				case Decision::MOVE_LEFT:
					if (posX[i] > stepValue)
						posX[i] -= stepValue;
					break;
				case Decision::MOVE_RIGHT:
					if (posX[i] < screen_width - stepValue)
						posY[i] += stepValue;
					break;
				}

				
			}
		}

		lastTime = currentTime;

		for (int i = 0; i < testAmount; ++i)
		{
			DrawCircle(*colors[i], posX[i], posY[i], tmpRadius);
		}

		//Here graph render function
		//DrawCircle(Colors::green, Colors::white, 50, 50, 50, 5);
		//DrawCircle(Colors::blue, 50, 100, 50);
		//DrawLine(Colors::red, 50, 50, 50, 100);

		GraphRenderer::RenderGraph(graph);

		SDL_RenderPresent(renderer);
	}

	Close();

	for (int i = 0; i < testAmount; ++i)
	{
		delete pawns[i];
		delete colors[i];
	}
	delete[] pawns;
	delete[] colors;
	delete[] posX;
	delete[] posY;

	delete graph;

	return 0;
}