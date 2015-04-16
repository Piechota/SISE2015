#include "Headers.h"
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
	if (!Init(700, 700))
		return 1;

	bool run = true;
	SDL_Event event;
	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				run = false;
		}

		SDL_SetRenderDrawColor(renderer, Colors::black.r, Colors::black.g, Colors::black.b, 0xFF);
		SDL_RenderClear(renderer);

		//Here graph render function
		DrawCircle(Colors::green, Colors::white, 300, 300, 50, 5);
		DrawCircle(Colors::blue, 400, 400, 50);
		DrawLine(Colors::red, 300, 300, 400, 400);

		SDL_RenderPresent(renderer);
	}
	Close();

	return 0;
}