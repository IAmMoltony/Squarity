#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Enemy.h"

class EnemySpawner
{
public:
    EnemySpawner(Enemy::List &enemies);
    ~EnemySpawner();

    void SpawnEnemies(int n);
    void SpawnEnemies(int n, Enemy::Type type);

private:
    Enemy::List &enemies;
};

#endif // ENEMYSPAWNER_H
