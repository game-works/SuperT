#include "levelmanager.h"

#include <QPixmapCache>

LevelManager::LevelManager() : level_(1), baseLife_(1), baseSpawn_(1000)
{
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

void LevelManager::processPlayerPoints(int points)
{
    if(points != 0 && points % 100 == 0)
    {
        level_++;
        emit increaseLevel();
    }
}

int LevelManager::currentLevel() const
{
    return level_;
}
