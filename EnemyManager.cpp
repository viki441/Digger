#include "EnemyManager.h"
#include <cstdlib> // rand
#include <ctime>

EnemyManager::EnemyManager(TextureManager* textures)
    : textures(textures)
{
    enemies[0] = new Enemy(textures); //always start with one
    enemyCount++;
}

void EnemyManager::addEnemy()
{
    if (enemyCount >= Constants::ENEMY_LIMIT - 1)
        return;

    enemies[enemyCount] = new Enemy(textures);
    enemyCount++;
}


EnemyManager::~EnemyManager()
{
    delete textures;
}


void EnemyManager::render(SDL_Renderer* r)
{
    for (Enemy* enemy : enemies)
    {
        enemy->render(r);
    }
}
const int EnemyManager::getCurrentCount() const
{
    return enemyCount;
}

Enemy* EnemyManager::getCurrentEnemy(int i)
{
    return enemies[i];
}

void EnemyManager::updateTime()
{
    if (time <= 0)
    {
        addEnemy();

        // random delay between spawns (e.g. 30–120 frames)
        time = 30 + (std::rand() % 90);
    }
    else
    {
        time--;
    }
}

void EnemyManager::update()
{

}