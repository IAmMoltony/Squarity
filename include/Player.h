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

    static void LoadSprites(SDL_Renderer *rend);
    static void UnloadSprites(void);

    Uint8 colorR, colorG, colorB;

    Player(int x, int y, Uint8 colorR, Uint8 colorG, Uint8 colorB);
    ~Player();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

    void Draw(SDL_Renderer *rend);
    void Update(Enemy::List &enemies, Trail::List &trails, SDL_Color &bgColor);
    void OnKeyPress(SDL_KeyboardEvent ev);
    void OnKeyRelease(SDL_KeyboardEvent ev);

    SDL_Rect GetRect(void) const;
    int GetHealth(void) const;

private:
    int x, y, velX, velY;
    int health;
    SDL_Texture *currentSprite;
    static SDL_Texture *spriteIdle, *spriteLeft, *spriteRight, *spriteUp, *spriteDown, *spriteUpLeft, *spriteUpRight,
                *spriteDownLeft, *spriteDownRight;

    void applyVelocity(void);
    void clampPosition(void);
    void checkCollision(Enemy::List &enemies, SDL_Color &bgColor);
    void updateTrail(Trail::List &trails);
    void updateSprite(void);
};

#endif // PLAYER_H
