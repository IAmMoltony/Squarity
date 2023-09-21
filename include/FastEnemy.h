#ifndef FASTENEMY_H
#define FASTENEMY_H

#include "BasicEnemy.h"

class FastEnemy : public BasicEnemy
{
public:
    FastEnemy(int x, int y);
    ~FastEnemy();

    SDL_Color GetColor(void) const override;

private:
    void initVelocity(void) override;
};

#endif // FASTENEMY_H
