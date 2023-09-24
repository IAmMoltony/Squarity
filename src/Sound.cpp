#include "Sound.h"
#include "sndload.h"

Sound::Sound() : sound(nullptr)
{
}

Sound::Sound(const char *path) : sound(nullptr)
{
    sound = LoadSound(path);
}

Sound::~Sound()
{
    Mix_FreeChunk(sound);
}

void Sound::Play(void)
{
    Mix_PlayChannel(-1, sound, 0);
}
