#include "Enemy.h"
#include "random.h"
#include "BasicEnemy.h"
#include "FastEnemy.h"
#include "SmartEnemy.h"

Enemy::Type Enemy::RandomType(void)
{
    return (Type)RandomRange(static_cast<int>(Type::Basic), static_cast<int>(Type::_Last) - 1);
}

Enemy::Pointer Enemy::CreateEnemyFromType(int x, int y, Enemy::Type type)
{
    switch (type) {
        case Type::Basic:
            return new BasicEnemy(x, y);
        case Type::Fast:
            return new FastEnemy(x, y);
        case Type::Smart:
            return new SmartEnemy(x, y);
        default:
            return nullptr;
    }
}

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
