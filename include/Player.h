#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Enemy.h"
#include "Trail.h"

class Player
{
public:
    static inline constexpr int WIDTH = 32;
    static inline constexpr int HEIGHT = 32;
    static inline constexpr int FULL_HEALTH = 150;

    Uint8 colorR, colorG, colorB;

    Player(int x, int y, Uint8 colorR, Uint8 colorG, Uint8 colorB);
    ~Player();

    void Draw(SDL_Renderer *rend);
    void Update(Enemy::List &enemies, Trail::List &trails);
    void OnKeyPress(SDL_KeyboardEvent ev);
    void OnKeyRelease(SDL_KeyboardEvent ev);

    SDL_Rect GetRect(void) const;
    int GetHealth(void) const;

private:
    int x, y, velX, velY;
    int health;

    void applyVelocity(void);
    void clampPosition(void);
    void checkCollision(Enemy::List &enemies);
    void updateTrail(Trail::List &trails);
};

#endif // PLAYER_H
