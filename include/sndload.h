#ifndef SNDLOAD_H
#define SNDLOAD_H

#include <SDL2/SDL_mixer.h>

#ifdef __cplusplus
extern "C" {
#endif

Mix_Chunk *LoadSound(const char *path);

#ifdef __cplusplus
}
#endif

#endif // SNDLOAD_H
