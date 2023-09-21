#include "textrender.h"

void RenderText(SDL_Renderer *rend, int x, int y, TTF_Font *ttfont, SDL_Color color, const char *text)
{
    SDL_Surface *surf = TTF_RenderText_Solid(ttfont, text, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surf);
    int w, h;
    TTF_SizeText(ttfont, text, &w, &h);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(rend, tex, NULL, &rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}
