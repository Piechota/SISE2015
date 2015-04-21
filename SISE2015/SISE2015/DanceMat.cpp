#include "Headers.h"


DanceMat::DanceMat()
{
	if (SDL_NumJoysticks() > 0)
	{
		dance_mat = SDL_JoystickOpen(0);
	}
}
void DanceMat::CloseDanceMat()
{
	if (dance_mat != nullptr)
		SDL_JoystickClose(dance_mat);
}

bool DanceMat::IsDanceMat() const
{
	return dance_mat != nullptr;
}
bool DanceMat::IsKeyDown(const int& key) const
{
	return SDL_JoystickGetButton(dance_mat, key) == (Uint8)1;
}

namespace DanceMatButtons
{
	const int UP = 2;
	const int RIGHT = 3;
	const int DOWN = 1;
	const int LEFT = 0;

	const int UP_RIGHT = 7;
	const int RIGHT_DOWN = 5;
	const int DOWN_LEFT = 4;
	const int LEFT_UP = 6;

	const int SELECT = 8;
	const int START = 9;
}