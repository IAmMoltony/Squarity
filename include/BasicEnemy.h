#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "Enemy.h"

class BasicEnemy : public Enemy
{
public:
    BasicEnemy(int x, int y);

    virtual void Draw(SDL_Renderer *rend) override;
    void Update(Trail::List &trails) override;

    int GetWidth(void) const override;
    int GetHeight(void) const override;
    Type GetType(void) const override;
    SDL_Rect GetRect(void) const override;
    virtual SDL_Color GetColor(void) const override;

private:
    virtual void initVelocity(void);
    void applyVelocity(void);
    void checkBounds(void);
    void updateTrail(Trail::List &trails);
};

#endif // BASICENEMY_H
