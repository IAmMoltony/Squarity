#ifndef IMGLOAD_H
#define IMGLOAD_H

#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

SDL_Texture *LoadImage(SDL_Renderer *rend, const char *path);

#ifdef __cplusplus
}
#endif

#endif // IMGLOAD_H
