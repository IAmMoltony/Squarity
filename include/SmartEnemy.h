#ifndef SMARTENEMY_H
#define SMARTENEMY_H

#include "Enemy.h"

class SmartEnemy : public Enemy
{
public:
    SmartEnemy(int x, int y);
    ~SmartEnemy();

    void Draw(SDL_Renderer *rend) override;
    void Update(Trail::List &trails, Particle::List &particles, int playerX, int playerY) override;

    int GetWidth(void) const;
    int GetHeight(void) const;
    Type GetType(void) const;
    SDL_Rect GetRect(void) const;
    SDL_Color GetColor(void) const;

private:
    int velBase;

    void applyVelocity(void);
    void followPlayer(int x, int y);
    void updateTrail(Trail::List &trails);
};

#endif // SMARTENEMY_H
