#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <cstdint>

static const uint8_t keysNum = 17;

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	bool IsKeyDown(const uint8_t key) const;
	void SetKeyDown(const uint8_t key);
	void ResetKeys();

private:
	uint8_t keys[keysNum];
};

namespace KeyboardButtons
{
	extern const uint8_t K0;
	extern const uint8_t K1;
	extern const uint8_t K2;
	extern const uint8_t K3;
	extern const uint8_t K4;
	extern const uint8_t K5;
	extern const uint8_t K6;
	extern const uint8_t K7;
	extern const uint8_t K8;
	extern const uint8_t K9;

	extern const uint8_t UP;
	extern const uint8_t DOWN;
	extern const uint8_t LEFT;
	extern const uint8_t RIGHT;

	extern const uint8_t ESCAPE;
	extern const uint8_t RETURN;
	extern const uint8_t SPACE;
}

#endif