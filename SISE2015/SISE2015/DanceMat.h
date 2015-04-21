#ifndef _DANCEMAT_H
#define _DANCEMAT_H

#include "Headers.h"

class DanceMat
{
private:
	SDL_Joystick* dance_mat;
public:
	DanceMat();

	void CloseDanceMat();
	bool IsKeyDown(const int& key) const;
	bool IsDanceMat() const;
};

namespace DanceMatButtons
{
	extern const int UP;
	extern const int RIGHT;
	extern const int DOWN;
	extern const int LEFT;

	extern const int UP_RIGHT;
	extern const int RIGHT_DOWN;
	extern const int DOWN_LEFT;
	extern const int LEFT_UP;

	extern const int SELECT;
	extern const int START;
}

#endif