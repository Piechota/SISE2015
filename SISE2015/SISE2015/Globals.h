#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;
class DanceMat;
class Audio;

extern uint16_t screen_width;
extern uint16_t screen_height;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern DanceMat* danceMat;
extern Audio* audio;

#ifdef _MSC_VER
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __attribute__((always_inline))
#endif

#endif
