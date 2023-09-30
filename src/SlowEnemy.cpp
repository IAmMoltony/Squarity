#include "SlowEnemy.h"

SlowEnemy::SlowEnemy(int x, int y) : BasicEnemy(x, y)
{
    initVelocity();
}

void SlowEnemy::initVelocity(void)
{
    velX = (std::rand() % 2) ? 2 : -2;
    velY = (std::rand() % 2) ? 2 : -2;
}

SlowEnemy::~SlowEnemy()
{
}

SDL_Color SlowEnemy::GetColor(void) const
{
    SDL_Color color;
    color.r = 139;
    color.g = 69;
    color.b = 19;
    return color;
}

Enemy::Type SlowEnemy::GetType(void) const
{
    return Type::Slow;
}
