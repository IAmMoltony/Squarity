#include "Trail.h"

Trail::Trail(int x, int y, int w, int h, Uint8 colorR, Uint8 colorG, Uint8 colorB) : x(x), y(y), w(w), h(h), a(255), r(colorR),
                                                                                     g(colorG), b(colorB)
{
}

Trail::~Trail()
{
}

void Trail::Draw(SDL_Renderer *rend)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(rend, r, g, b, (Uint8)a);
    SDL_RenderFillRect(rend, &rect);
}

void Trail::Update(void)
{
    a -= 10;
    if (a < 0)
        a = 0;
}

Uint8 Trail::GetAlpha(void)
{
    return (Uint8)a;
}
