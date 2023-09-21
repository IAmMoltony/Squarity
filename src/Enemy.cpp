#include "Enemy.h"

Enemy::Enemy(int x, int y) : x(x), y(y), velX(0), velY(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::InvertVelocity(void)
{
    velX *= -1;
    velY *= -1;
}
