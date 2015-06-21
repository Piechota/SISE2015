#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;
class DanceMat;
class Audio;
class Keyboard;
class GameController;

extern uint16_t screen_width;
extern uint16_t screen_height;
extern bool run;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern DanceMat* danceMat;
extern Audio* audio;
extern Keyboard* keyboard;
extern GameController* game;

extern uint32_t lastTime;
extern uint32_t currentTime;
extern uint32_t deltaTime;

void RefreshInputAndScreen();

#ifdef _MSC_VER
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __attribute__((always_inline))
#endif

#ifdef _MSC_VER
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

#endif
