#ifndef TEXTRENDER_H
#define TEXTRENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifdef __cplusplus
extern "C" {
#endif

void RenderText(SDL_Renderer *rend, int x, int y, TTF_Font *ttfont, SDL_Color color, const char *text);

#ifdef __cplusplus
}
#endif

#endif // TEXTRENDER_H
