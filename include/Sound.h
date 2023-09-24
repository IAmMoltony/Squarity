#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>

class Sound
{
public:
    Sound();
    Sound(const char *path);
    ~Sound();

    Sound(Sound &) = delete;
    Sound &operator=(Sound &) = delete;

    void Play(void);

private:
    Mix_Chunk *sound;
};

#endif // SOUND_H
