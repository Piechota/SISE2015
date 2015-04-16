#ifndef _RENDERER_H
#define _RENDERER_H

//Line
extern void DrawLine(const Color& color, const SDL_Point& p0, const SDL_Point& p1);
extern void DrawLine(const Color& color, const int& x0, const int& y0, const int& x1, const int& y1);
extern void DrawLine(const Color& color, const float& x0, const float& y0, const float& x1, const float& y1);

//Circle without border
extern void DrawCircle(const Color& color, const int& x, const int& y, const int& radius);
extern void DrawCircle(const Color& color, const SDL_Point& p, const int& radius);
extern void DrawCircle(const Color& color, const float& x, const float& y, const float& radius);

//Circle with border
extern void DrawCircle(const Color& fillColor, const Color& borderColor, const int& x, const int& y, const int& radius, const int& borderSize);
extern void DrawCircle(const Color& fillColor, const Color& borderColor, const SDL_Point& p, const int& radius, const int& borderSize);
extern void DrawCircle(const Color& fillColor, const Color& borderColor, const float& x, const float& y, const float& radius, const float& borderSize);
#endif