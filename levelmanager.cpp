#include "levelmanager.h"

LevelManager::LevelManager() : level_(1), baseLife_(1), baseSpawn_(1000), playerPoints_(0), playerSpecials_(0)
{
}

void LevelManager::increasePlayerPoint()
{
    ++playerPoints_;
    if(playerPoints_ != 0 && (playerPoints_ % (LEVEL_MANAGER_POINT_BASE * level_)) == 0) // increase the level size as level increases
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


QString LevelManager::currentBackground()
{
    auto b = level_ % 7; // there are 7 background images...
    QString background = QString("background_%1").arg(b);
    return background;
}

int LevelManager::enemyLifeBase()
{
    return static_cast<int>(log(level_) + 1); // 1 life points base
}

qreal LevelManager::enemySpawnBase()
{
    return (1.0/level_);
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
