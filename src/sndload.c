#include "sndload.h"
#include <SDL2/SDL.h>

Mix_Chunk *LoadSound(const char *path)
{
#ifdef DEBUG
    SDL_Log("Loading sound %s\n", path);
#endif

    Mix_Chunk *snd = Mix_LoadWAV(path);
    if (!snd) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound %s because %s\n", path, Mix_GetError());
        return NULL;
    }

    return snd;
}
