#include "specialcommand.h"

#include "game.h"

#include <QDebug>

SpecialCommand::SpecialCommand() : cooldown_(0)
{
    cooldown_ = QTime::currentTime().msecsSinceStartOfDay();
}

void SpecialCommand::execute(Game *game, QSharedPointer<Entity> entity, int elapsedTime)
{
    Q_UNUSED(entity)
    Q_UNUSED(elapsedTime)
    if(game->playerSpecials() > 0)
    {
        timestamp_ = QTime::currentTime().msecsSinceStartOfDay();
        if(timestamp_ > cooldown_ + SPECIAL_COOL_DOWN)
        {
            if(game != nullptr)
            {
                game->createSpecial();
            }
            cooldown_ = timestamp_;
            game->specialCoolDownWarning(SPECIAL_COOL_DOWN);
        }
    }
}
