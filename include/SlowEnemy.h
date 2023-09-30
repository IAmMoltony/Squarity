#ifndef SLOWENEMY_H
#define SLOWENEMY_H

#include "BasicEnemy.h"

class SlowEnemy : public BasicEnemy
{
public:
    SlowEnemy(int x, int y);
    ~SlowEnemy();

    SDL_Color GetColor(void) const override;
    Type GetType(void) const override;

private:
    void initVelocity(void) override;
};

#endif // SLOWENEMY_H
