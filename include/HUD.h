#ifndef HUD_H
#define HUD_H

#include "Player.h"
#include <SDL2/SDL_ttf.h>

class HUD
{
public:
    HUD(const Player *player, int *score, int *level);
    ~HUD();

    HUD(const HUD &) = delete;
    HUD &operator=(const HUD &) = delete;

    void Draw(SDL_Renderer *rend);

private:
    const Player *player;
    int *score, *level;
    TTF_Font *font8;
};

#endif // HUD_H
