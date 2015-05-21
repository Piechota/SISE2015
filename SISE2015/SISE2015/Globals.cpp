#include "Globals.h"
#include "Keyboard.h"
#include "Colour.h"
#include "GameController.h"
#include <SDL.h>
#include <fl\Headers.h>

uint16_t screen_width;
uint16_t screen_height;
bool run = true;

SDL_Window* window;
SDL_Renderer* renderer;
DanceMat* danceMat;
Audio* audio;
Keyboard* keyboard;
GameController* game;

fl::Engine* fuzzyEngine;

uint32_t lastTime = 0;
uint32_t currentTime = 0;
uint32_t deltaTime = 0;

void RefreshInputAndScreen()
{
	SDL_Event event;

	currentTime = SDL_GetTicks();
	if (currentTime <= lastTime) return;
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	keyboard->ResetKeys();

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			run = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_0:
				keyboard->SetKeyDown(KeyboardButtons::K0);
				break;

			case SDLK_1:
				keyboard->SetKeyDown(KeyboardButtons::K1);
				break;

			case SDLK_2:
				keyboard->SetKeyDown(KeyboardButtons::K2);
				break;

			case SDLK_3:
				keyboard->SetKeyDown(KeyboardButtons::K3);
				break;

			case SDLK_4:
				keyboard->SetKeyDown(KeyboardButtons::K4);
				break;

			case SDLK_5:
				keyboard->SetKeyDown(KeyboardButtons::K5);
				break;

			case SDLK_6:
				keyboard->SetKeyDown(KeyboardButtons::K6);
				break;

			case SDLK_7:
				keyboard->SetKeyDown(KeyboardButtons::K7);
				break;

			case SDLK_8:
				keyboard->SetKeyDown(KeyboardButtons::K8);
				break;

			case SDLK_9:
				keyboard->SetKeyDown(KeyboardButtons::K9);
				break;

			case SDLK_UP:
				keyboard->SetKeyDown(KeyboardButtons::UP);
				break;

			case SDLK_DOWN:
				keyboard->SetKeyDown(KeyboardButtons::DOWN);
				break;

			case SDLK_LEFT:
				keyboard->SetKeyDown(KeyboardButtons::LEFT);
				break;

			case SDLK_RIGHT:
				keyboard->SetKeyDown(KeyboardButtons::RIGHT);
				break;

			case SDLK_ESCAPE:
				keyboard->SetKeyDown(KeyboardButtons::ESCAPE);
				break;

			case SDLK_RETURN:
				keyboard->SetKeyDown(KeyboardButtons::RETURN);
				break;

			case SDLK_SPACE:
				keyboard->SetKeyDown(KeyboardButtons::SPACE);
				break;

			default:
				break;
			}
		}
	}

	Colours::background = Colour(255, (Uint8)(255 * sin(currentTime / 300.0f)), 150);
	game->Render();

	//std::cout << deltaTime << std::endl;
	if (deltaTime < 16) SDL_Delay(16 - deltaTime);
}