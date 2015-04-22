#include <cmath>
#include <SDL.h>
#include "Globals.h"
#include "Renderer.h"
#include "Color.h"

int length(const int& x0, const int& y0, const int& x1, const int& y1)
{
	const int w2 = (x1 - x0) * (x1 - x0);
	const int h2 = (y1 - y0) * (y1 - y0);

	return (int)sqrt(w2 + h2);
}

void DrawLine(const Color& color, const SDL_Point& p0, const SDL_Point& p1)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
}

void DrawLine(const Color& color, const int& x0, const int& y0, const int& x1, const int& y1)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

void DrawLine(const Color& color, const float& x0, const float& y0, const float& x1, const float& y1)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	//SDL_RenderDrawLine(renderer, (int)(x0 * screen_width), (int)(y0 * screen_height), (int)(x1 * screen_width), (int)(y1 * screen_height));
	SDL_RenderDrawLine(renderer, (int)x0, (int)y0, (int)x1, (int)y1);
}


void DrawCircleImpl(const Color& color, const int& x, const int& y, const int& radius)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	const Uint32 rmask = 0xff000000;
	const Uint32 gmask = 0x00ff0000;
	const Uint32 bmask = 0x0000ff00;
	const Uint32 amask = 0x000000ff;
#else
	const Uint32 rmask = 0x000000ff;
	const Uint32 gmask = 0x0000ff00;
	const Uint32 bmask = 0x00ff0000;
	const Uint32 amask = 0xff000000;
#endif

	const int side = 2 * radius;
	const static int cRadius = screen_height / 2;

	SDL_Surface* sCircle = SDL_CreateRGBSurface(0, screen_width, screen_height, 32, rmask, gmask, bmask, amask);
	Uint8* pixels = (Uint8*)sCircle->pixels;

	for (size_t X = 0; X < screen_width; X += 4)
	{
		for (size_t Y = 0; Y < screen_height; Y += 4)
		{
			if (length(X, Y, cRadius, cRadius) <= cRadius)
			{
				pixels[Y * screen_width + X + 0] = color.r;
				pixels[Y * screen_width + X + 1] = color.g;
				pixels[Y * screen_width + X + 2] = color.b;
				pixels[Y * screen_width + X + 3] = 0xFF;
			}
			else
			{
				pixels[Y * screen_width + X + 0] = 0x00;
				pixels[Y * screen_width + X + 1] = 0x00;
				pixels[Y * screen_width + X + 2] = 0x00;
				pixels[Y * screen_width + X + 3] = 0x00;
			}
		}
	}

	SDL_Texture* tCircle = SDL_CreateTextureFromSurface(renderer, sCircle);
	SDL_Rect position = SDL_Rect();
	position.h = side * 2;
	position.w = side * 2;
	position.x = x - radius / 2;
	position.y = y - radius / 2;

	SDL_RenderCopy(renderer, tCircle, NULL, &position);
	SDL_FreeSurface(sCircle);
	SDL_DestroyTexture(tCircle);
}

void DrawCircle(const Color& color, const int& x, const int& y, const int& radius)
{
	DrawCircleImpl(color, x, y, radius);
}

void DrawCircle(const Color& color, const SDL_Point& p, const int& radius)
{
	DrawCircleImpl(color, p.x, p.y, radius);
}

void DrawCircle(const Color& color, const float& x, const float& y, const float& radius)
{
	//DrawCircleImpl(color, x * screen_width, y * screen_height, fmax(radius * screen_height, radius * screen_width));
	DrawCircleImpl(color, (int)x, (int)y, (int)radius);
}

void DrawCircleImpl(const Color& fillColor, const Color& borderColor, const int& x, const int& y, const int& radius, const int& borderSize)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	const Uint32 rmask = 0xff000000;
	const Uint32 gmask = 0x00ff0000;
	const Uint32 bmask = 0x0000ff00;
	const Uint32 amask = 0x000000ff;
#else
	const Uint32 rmask = 0x000000ff;
	const Uint32 gmask = 0x0000ff00;
	const Uint32 bmask = 0x00ff0000;
	const Uint32 amask = 0xff000000;
#endif

	const int side = 2 * radius;
	const static int cRadius = screen_height / 2;
	const int bSize = (borderSize * cRadius) / radius;
	SDL_Surface* sCircle = SDL_CreateRGBSurface(0, screen_width, screen_height, 32, rmask, gmask, bmask, amask);
	Uint8* pixels = (Uint8*)sCircle->pixels;

	int l;

	for (size_t X = 0; X < screen_width; X += 4)
	{
		for (size_t Y = 0; Y < screen_height; Y += 4)
		{
			if ((l = length(X, Y, cRadius, cRadius)) <= cRadius)
			{
				if (l > cRadius - bSize)
				{
					pixels[Y * screen_width + X + 0] = borderColor.r;
					pixels[Y * screen_width + X + 1] = borderColor.g;
					pixels[Y * screen_width + X + 2] = borderColor.b;
					pixels[Y * screen_width + X + 3] = 0xFF;
				}
				else
				{
					pixels[Y * screen_width + X + 0] = fillColor.r;
					pixels[Y * screen_width + X + 1] = fillColor.g;
					pixels[Y * screen_width + X + 2] = fillColor.b;
					pixels[Y * screen_width + X + 3] = 0xFF;
				}
			}
			else
			{
				pixels[Y * screen_width + X + 0] = 0x00;
				pixels[Y * screen_width + X + 1] = 0x00;
				pixels[Y * screen_width + X + 2] = 0x00;
				pixels[Y * screen_width + X + 3] = 0x00;
			}
		}
	}

	SDL_Texture* tCircle = SDL_CreateTextureFromSurface(renderer, sCircle);
	SDL_Rect position = SDL_Rect();
	position.h = side * 2;
	position.w = side * 2;
	position.x = x - radius / 2;
	position.y = y - radius / 2;

	SDL_RenderCopy(renderer, tCircle, NULL, &position);
	SDL_FreeSurface(sCircle);
	SDL_DestroyTexture(tCircle);
}

void DrawCircle(const Color& fillColor, const Color& borderColor, const int& x, const int& y, const int& radius, const int& borderSize)
{
	DrawCircleImpl(fillColor, borderColor, x, y, radius, borderSize);
}

void DrawCircle(const Color& fillColor, const Color& borderColor, const SDL_Point& p, const int& radius, const int& borderSize)
{
	DrawCircleImpl(fillColor, borderColor, p.x, p.y, radius, borderSize);
}

void DrawCircle(const Color& fillColor, const Color& borderColor, const float& x, const float& y, const float& radius, const float& borderSize)
{
	//DrawCircleImpl(fillColor, borderColor, x * screen_width, y * screen_height, radius * screen_height, borderSize * screen_height);
	DrawCircleImpl(fillColor, borderColor, (int)x, (int)y, (int)radius, (int)borderSize);
}
