#include "Headers.h"

DanceMat::DanceMat()
{
	if (SDL_NumJoysticks() > 0)
	{
		dance_mat = SDL_JoystickOpen(0);
	}
}

DanceMat::~DanceMat()
{
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

bool DanceMat::IsKeyDown(const uint8_t& key) const
{
	return SDL_JoystickGetButton(dance_mat, key) == (Uint8)1;
}

namespace DanceMatButtons
{
	const uint8_t UP = 2;
	const uint8_t RIGHT = 3;
	const uint8_t DOWN = 1;
	const uint8_t LEFT = 0;

	const uint8_t UP_RIGHT = 7;
	const uint8_t RIGHT_DOWN = 5;
	const uint8_t DOWN_LEFT = 4;
	const uint8_t LEFT_UP = 6;

	const uint8_t SELECT = 8;
	const uint8_t START = 9;
}