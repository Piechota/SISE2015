#ifndef _DANCEMAT_H
#define _DANCEMAT_H

#include "Headers.h"

class DanceMat
{
public:
	DanceMat();

	void CloseDanceMat();
	bool IsKeyDown(const uint8_t& key) const;
	bool IsDanceMat() const;

private:
	SDL_Joystick* dance_mat;
};

namespace DanceMatButtons
{
	extern const uint8_t UP;
	extern const uint8_t RIGHT;
	extern const uint8_t DOWN;
	extern const uint8_t LEFT;

	extern const uint8_t UP_RIGHT;
	extern const uint8_t RIGHT_DOWN;
	extern const uint8_t DOWN_LEFT;
	extern const uint8_t LEFT_UP;

	extern const uint8_t SELECT;
	extern const uint8_t START;
}

#endif