#include "imgload.h"
#include <SDL2/SDL_image.h>
#include <errno.h>

SDL_Texture *LoadImage(SDL_Renderer *rend, const char *path)
{
#ifdef DEBUG
    SDL_Log("Loading image %s\n", path);
#endif

    SDL_Surface *surf = IMG_Load(path);
    if (!surf) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load %s because %s\n", path, strerror(errno));
        return NULL;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);
    return tex;
}
