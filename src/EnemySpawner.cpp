#include "EnemySpawner.h"
#include "random.h"

EnemySpawner::EnemySpawner(Enemy::List &enemies) : enemies(enemies)
{
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::SpawnEnemies(int n)
{
    Enemy::Type type = Enemy::RandomType();
    for (int i = 0; i < n; i++) {
        Enemy::Pointer enemy = Enemy::CreateEnemyFromType(RandomRange(0, 800 - 32), RandomRange(0, 600 - 32), type);
        enemies.push_back(enemy);
    }
}

void EnemySpawner::SpawnEnemies(int n, Enemy::Type type)
{
    for (int i = 0; i < n; i++) {
        Enemy::Pointer enemy = Enemy::CreateEnemyFromType(RandomRange(0, 800 - 32), RandomRange(0, 600 - 32), type);
        enemies.push_back(enemy);
    }
}
