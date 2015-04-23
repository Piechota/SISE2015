#ifndef _RENDERER_H
#define _RENDERER_H

struct Color;
struct SDL_Point;

//Line
extern void DrawLine(const Color& color, const SDL_Point& p0, const SDL_Point& p1);
extern void DrawLine(const Color& color, const int32_t& x0, const int32_t& y0, const int32_t& x1, const int32_t& y1);
extern void DrawLine(const Color& color, const float& x0, const float& y0, const float& x1, const float& y1);

//Circle without border
extern void DrawCircle(const Color& color, const int32_t& x, const int32_t& y, const uint32_t& radius);
extern void DrawCircle(const Color& color, const SDL_Point& p, const uint32_t& radius);
extern void DrawCircle(const Color& color, const float& x, const float& y, const float& radius);

//Circle with border
extern void DrawCircle(const Color& fillColor, const Color& borderColor, const int32_t& x, const int32_t& y, const uint32_t& radius, const uint32_t& borderSize);
extern void DrawCircle(const Color& fillColor, const Color& borderColor, const SDL_Point& p, const uint32_t& radius, const uint32_t& borderSize);
extern void DrawCircle(const Color& fillColor, const Color& borderColor, const float& x, const float& y, const float& radius, const float& borderSize);

#endif