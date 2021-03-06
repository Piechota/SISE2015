#include <cmath>
#include <map>
#include <unordered_map>
#include <SDL.h>
#include "Globals.h"
#include "Renderer.h"
#include "Colour.h"

std::unordered_map<const Colour*, SDL_Texture*> circleTextures;
std::map<std::pair<const Colour*, const Colour*>, SDL_Texture*> circleTexturesBorder;

FORCEINLINE uint32_t length(const size_t& x0, const size_t& y0, const int32_t& x1, const int32_t& y1)
{
	const size_t w2 = (x1 - x0) * (x1 - x0);
	const size_t h2 = (y1 - y0) * (y1 - y0);

	return (uint32_t)sqrt(w2 + h2);
}

FORCEINLINE void DrawLine(const Colour& color, const SDL_Point& p0, const SDL_Point& p1)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
}

FORCEINLINE void DrawLine(const Colour& color, const int32_t& x0, const int32_t& y0, const int32_t& x1, const int32_t& y1)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

FORCEINLINE void DrawLine(const Colour& color, const float& x0, const float& y0, const float& x1, const float& y1)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawLine(renderer, (int32_t)(x0 * screen_width), (int32_t)(y0 * screen_height), (int32_t)(x1 * screen_width), (int32_t)(y1 * screen_height));
	//SDL_RenderDrawLine(renderer, (int32_t)x0, (int32_t)y0, (int32_t)x1, (int32_t)y1);
}

FORCEINLINE void DrawCircleImpl(const Colour& color, const int32_t* RESTRICT const x, const int32_t* RESTRICT const y, const uint32_t& radius, const size_t num)
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

	const uint32_t side = 2 * radius;
	static const uint32_t cRadius = screen_height / 2;

	if (circleTextures.find(&color) == circleTextures.end())
	{
		SDL_Surface* const sCircle = SDL_CreateRGBSurface(0, screen_width, screen_height, 32, rmask, gmask, bmask, amask);
		Uint8* RESTRICT const pixels = (Uint8*)sCircle->pixels;

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

		SDL_Texture* const tCircle = SDL_CreateTextureFromSurface(renderer, sCircle);

		circleTextures.insert(std::make_pair(&color, tCircle));

		SDL_FreeSurface(sCircle);
		//SDL_DestroyTexture(tCircle);
	}

	SDL_Texture* const circleTexture = circleTextures[&color];

	SDL_Rect position = SDL_Rect();
	position.h = side * 2;
	position.w = side * 2;

	for (size_t i = 0; i < num; ++i)
	{
		position.x = x[i] - radius / 2;
		position.y = y[i] - radius / 2;

		SDL_RenderCopy(renderer, circleTexture, NULL, &position);
	}
}

void DrawCircle(const Colour& color, const int32_t& x, const int32_t& y, const uint32_t& radius)
{
	DrawCircleImpl(color, &x, &y, radius, 1);
}

void DrawCircle(const Colour& color, const SDL_Point& p, const uint32_t& radius)
{
	DrawCircleImpl(color, &p.x, &p.y, radius, 1);
}

void DrawCircle(const Colour& color, const float& x, const float& y, const float& radius)
{
	const int32_t X = (int32_t)(x * screen_width);
	const int32_t Y = (int32_t)(y * screen_height);
	DrawCircleImpl(color, &X, &Y, (uint32_t)fmax(radius * screen_height, radius * screen_width), 1);
	//DrawCircleImpl(color, (int32_t)x, (int32_t)y, (uint32_t)radius);
}

void DrawCircle(const Colour& color, const int32_t* const x, const int32_t* const y, const uint32_t& radius, const size_t num)
{
	DrawCircleImpl(color, x, y, radius, num);
}

FORCEINLINE void DrawCircleImpl(const Colour& fillColor, const Colour& borderColor, const int32_t* RESTRICT const x, const int32_t* RESTRICT const y, const uint32_t& radius, const uint32_t& borderSize, const size_t num)
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

	const uint32_t side = 2 * radius;
	static const uint32_t cRadius = screen_height / 2;
	const uint32_t bSize = (borderSize * cRadius) / radius;

	std::pair<const Colour*, const Colour*> key = std::make_pair(&fillColor, &borderColor);

	if (circleTexturesBorder.find(key) == circleTexturesBorder.end())
	{
		SDL_Surface* const sCircle = SDL_CreateRGBSurface(0, screen_width, screen_height, 32, rmask, gmask, bmask, amask);
		Uint8* RESTRICT const pixels = (Uint8*)sCircle->pixels;

		uint32_t l;

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

		SDL_Texture* const tCircle = SDL_CreateTextureFromSurface(renderer, sCircle);

		circleTexturesBorder.insert(std::make_pair(key, tCircle));

		SDL_FreeSurface(sCircle);
		//SDL_DestroyTexture(tCircle);
	}

	SDL_Texture* const circleTexture = circleTexturesBorder[key];

	SDL_Rect position = SDL_Rect();
	position.h = side * 2;
	position.w = side * 2;

	for (size_t i = 0; i < num; ++i)
	{
		position.x = x[i] - radius / 2;
		position.y = y[i] - radius / 2;

		SDL_RenderCopy(renderer, circleTexture, NULL, &position);
	}
}

void DrawCircle(const Colour& fillColor, const Colour& borderColor, const int32_t& x, const int32_t& y, const uint32_t& radius, const uint32_t& borderSize)
{
	DrawCircleImpl(fillColor, borderColor, &x, &y, radius, borderSize, 1);
}

void DrawCircle(const Colour& fillColor, const Colour& borderColor, const SDL_Point& p, const uint32_t& radius, const uint32_t& borderSize)
{
	DrawCircleImpl(fillColor, borderColor, &p.x, &p.y, radius, borderSize, 1);
}

void DrawCircle(const Colour& fillColor, const Colour& borderColor, const float& x, const float& y, const float& radius, const float& borderSize)
{
	const int32_t X = (int32_t)(x * screen_width);
	const int32_t Y = (int32_t)(y * screen_height);
	DrawCircleImpl(fillColor, borderColor, &X, &Y, (uint32_t)(radius * screen_height), (uint32_t)(borderSize * screen_height), 1);
	//DrawCircleImpl(fillColor, borderColor, (int32_t)x, (int32_t)y, (uint32_t)radius, (uint32_t)borderSize);
}

void DrawCircle(const Colour& fillColor, const Colour& borderColor, const int32_t* const x, const int32_t* const y, const uint32_t& radius, const uint32_t& borderSize, const size_t num)
{
	DrawCircleImpl(fillColor, borderColor, x, y, radius, borderSize, num);
}
