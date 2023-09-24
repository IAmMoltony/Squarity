#include "FastEnemy.h"

FastEnemy::FastEnemy(int x, int y) : BasicEnemy(x, y)
{
    initVelocity();
}

void FastEnemy::initVelocity(void)
{
    velX = (std::rand() % 2) ? 3 : -3;
    velY = (std::rand() % 2) ? 7 : -7;
}

FastEnemy::~FastEnemy()
{
}

SDL_Color FastEnemy::GetColor(void) const
{
    SDL_Color color;
    color.r = 0;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    return color;
}

Enemy::Type FastEnemy::GetType(void) const
{
    return Type::Fast;
}
