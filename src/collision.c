#include "collision.h"

bool RectIntersects(const SDL_Rect *a, const SDL_Rect *b)
{
    // I don't know what this does
    return !(a->x + a->w <= b->x || b->x + b->w <= a->x ||
        a->y + a->h <= b->y || b->y + b->h <= a->y);
}
