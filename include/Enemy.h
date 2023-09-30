#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <vector>
#include "Trail.h"
#include "Particle.h"

class Enemy
{
public:
    enum class Type
    {
        Basic,
        Fast,
        Smart,
        _Last,
    };

    typedef Enemy *Pointer;
    typedef std::vector<Pointer> List;

    static Type RandomType(void);
    static Pointer CreateEnemyFromType(int x, int y, Type type);

    Enemy(int x, int y);
    virtual ~Enemy();

    virtual void Draw(SDL_Renderer *rend) = 0;
    virtual void Update(Trail::List &trails, Particle::List &particles, int playerX, int playerY) = 0;

    void InvertVelocity(void);

    virtual int GetWidth(void) const = 0;
    virtual int GetHeight(void) const = 0;
    virtual Type GetType(void) const = 0;
    virtual SDL_Rect GetRect(void) const = 0;
    virtual SDL_Color GetColor(void) const = 0;

protected:
    int x, y, velX, velY;
};

#endif // ENEMY_H
