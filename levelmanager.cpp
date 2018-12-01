#include "levelmanager.h"

LevelManager::LevelManager() : level_(1), baseLife_(1), baseSpawn_(1000), playerPoints_(0), playerSpecials_(0)
{
}

void LevelManager::increasePlayerPoint()
{
    playerPoints_ += LEVEL_MANAGER_POINT_BASE;
    if(playerPoints_ != 0 && (playerPoints_ % (LEVEL_MANAGER_POINT_THRESHOLD * level_)) == 0) // increase the level size as level increases
    {
        level_++;
        emit increaseLevel();
    }

    if(playerPoints_ % LEVEL_MANAGER_SPECIAL_BASE == 0)
    {
        playerSpecials_++;
    }

    if(playerPoints_ % LEVEL_MANAGER_LIFE_BASE == 0)
    {
        emit increaseLife();
    }
}

void LevelManager::consumePlayerSpecial()
{
    playerSpecials_--;
}

int LevelManager::currentBackground()
{
    // there are 7 background images... start from 2
    return (level_ % 7);
}

int LevelManager::enemyLifeBase()
{
    return level_;
}

qreal LevelManager::enemySpawnBase()
{
    return level_ * 50;
}

int LevelManager::playerSpecials() const
{
    return playerSpecials_;
}

int LevelManager::playerPoints() const
{
    return playerPoints_;
}

int LevelManager::currentLevel() const
{
    return level_;
}

void LevelManager::reset()
{
    level_ = 1;
    baseLife_ = 1;
    baseSpawn_ = 1000;
    playerPoints_ = 0;
    playerSpecials_ = 0;
}
