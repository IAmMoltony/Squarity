#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool RectIntersects(const SDL_Rect *a, const SDL_Rect *b);

#ifdef __cplusplus
}
#endif

#endif // COLLISION_H
