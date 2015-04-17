#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <SDL.h>

#include "DataStructures.h"
#include "Globals.h"

#include "Pawn.h"
#include "Player.h"
#include "ExamplePlayer.h"
#include "HumanPlayer.h"
#include "GameController.h"

#include "Graph.h"
#include "Renderer.h"
#include "GraphRenderer.h"
#include "Stats.h"

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
	if (window == nullptr)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
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
	if (!Init(640, 640))
		return 1;

	bool run = true;
	SDL_Event event;

	//Stats* stats = new Stats("stats.csv");

	
	GameController* game = new GameController();
	game->Init();
	game->SubmitPlayer(new ExamplePlayer("Bot"));
	game->SubmitPlayer(new HumanPlayer("Mateusz"));

	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				run = false;
		}


		SDL_SetRenderDrawColor(renderer, Colors::black.r, Colors::black.g, Colors::black.b, 0xFF);
		SDL_RenderClear(renderer);

		game->MainLoop();

		//for (int i = 0; i < testAmount; ++i)
		//{
		//	DrawCircle(*colors[i], posX[i], posY[i], tmpRadius);
		//}

		//Here graph render function
		//DrawCircle(Colors::green, Colors::white, 50, 50, 50, 5);
		//DrawCircle(Colors::blue, 50, 100, 50);
		//DrawLine(Colors::red, 50, 50, 50, 100);

		SDL_RenderPresent(renderer);
	}

	Close();

	//stats->SaveToFile();

	//delete stats;

	return 0;
}