#include "Headers.h"

bool InitSDL(const int& w, const int& h)
{
    screen_width = w;
    screen_height = h;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void CloseSDL()
{
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[])
{
    srand(time(nullptr));
    if (!InitSDL(300, 300))
    {
        return 1;
    }

    danceMat = new DanceMat();
    audio = new Audio();
    keyboard = new Keyboard();
    game = new GameController();
    game->Init();

    audio->Play();

    while (run)
    {
        RefreshInputAndScreen();

        game->MainLoop();

        if (game->GetIsGameOver()) {
            run = false;
        }
    }

    game->SaveStats();
    delete game;

    danceMat->CloseDanceMat();
    delete danceMat;
    audio->Stop();
    delete audio;

    delete keyboard;
    CloseSDL();

    return 0;
}
