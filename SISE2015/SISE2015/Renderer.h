#ifndef _RENDERER_H
#define _RENDERER_H

struct Colour;
struct SDL_Point;

//Line
extern void DrawLine(const Colour& color, const SDL_Point& p0, const SDL_Point& p1);
extern void DrawLine(const Colour& color, const int32_t& x0, const int32_t& y0, const int32_t& x1, const int32_t& y1);
extern void DrawLine(const Colour& color, const float& x0, const float& y0, const float& x1, const float& y1);

//Circle without border
extern void DrawCircle(const Colour& color, const int32_t& x, const int32_t& y, const uint32_t& radius);
extern void DrawCircle(const Colour& color, const SDL_Point& p, const uint32_t& radius);
extern void DrawCircle(const Colour& color, const float& x, const float& y, const float& radius);

extern void DrawCircle(const Colour& color, const int32_t* const x, const int32_t* const y, const uint32_t& radius, const size_t num);

//Circle with border
extern void DrawCircle(const Colour& fillColor, const Colour& borderColor, const int32_t& x, const int32_t& y, const uint32_t& radius, const uint32_t& borderSize);
extern void DrawCircle(const Colour& fillColor, const Colour& borderColor, const SDL_Point& p, const uint32_t& radius, const uint32_t& borderSize);
extern void DrawCircle(const Colour& fillColor, const Colour& borderColor, const float& x, const float& y, const float& radius, const float& borderSize);

extern void DrawCircle(const Colour& fillColor, const Colour& borderColor, const int32_t* const x, const int32_t* const y, const uint32_t& radius, const uint32_t& borderSize, const size_t num);

#endif