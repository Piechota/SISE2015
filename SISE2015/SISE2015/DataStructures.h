#ifndef _DATASTRUCTURES_H_
#define _DATASTRUCTURES_H_

struct Vector2
{
	Vector2() { x = 0.0f; y = 0.0f; }
	Vector2(float x, float y, float z) : x(x), y(y) { }
	float x, y;
};

#endif