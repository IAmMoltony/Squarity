#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <vector>

class Enemy
{
public:
    enum class Type
    {
        Basic,
    };

    typedef Enemy *Pointer;
    typedef std::vector<Pointer> List;

    Enemy(int x, int y);
    virtual ~Enemy();

    virtual void Draw(SDL_Renderer *rend) = 0;
    virtual void Update(void) = 0;

    virtual int GetWidth(void) const = 0;
    virtual int GetHeight(void) const = 0;
    virtual Type GetType(void) const = 0;
    virtual SDL_Rect GetRect(void) const = 0;

protected:
    int x, y, velX, velY;
};

#endif // ENEMY_H
