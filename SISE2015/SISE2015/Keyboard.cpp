#include "Keyboard.h"
#include <cstring>

Keyboard::Keyboard()
{
	
}

Keyboard::~Keyboard()
{

}

bool Keyboard::IsKeyDown(const uint8_t key) const
{
	if (key >= keysNum) return false;
	return keys[key] == 1;
}

void Keyboard::SetKeyDown(const uint8_t key)
{
	if (key >= keysNum) return;
	keys[key] = 1;
}

void Keyboard::ResetKeys()
{
	memset(keys, 0, keysNum);
}

namespace KeyboardButtons
{
	const uint8_t K0 = 0;
	const uint8_t K1 = 1;
	const uint8_t K2 = 2;
	const uint8_t K3 = 3;
	const uint8_t K4 = 4;
	const uint8_t K5 = 5;
	const uint8_t K6 = 6;
	const uint8_t K7 = 7;
	const uint8_t K8 = 8;
	const uint8_t K9 = 9;

	const uint8_t UP = 10;
	const uint8_t DOWN = 11;
	const uint8_t LEFT = 12;
	const uint8_t RIGHT = 13;

	const uint8_t ESCAPE = 14;
	const uint8_t RETURN = 15;
	const uint8_t SPACE = 16;
}