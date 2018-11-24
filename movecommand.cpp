#include "movecommand.h"

#include "game.h"
#include "entity.h"

#include <QDebug>

MoveCommand::MoveCommand(DIRECTION dir) : dir_(dir)
{}

void MoveCommand::execute(Game* game, QSharedPointer<Entity> entity, int elapsedTime)
{
    Q_UNUSED(elapsedTime)
    Q_UNUSED(game)
    if(entity != nullptr)
    {
        switch (dir_)
        {
            case DIR_LEFT:
            {
                if(entity->position().x() > 0)
                    entity->move(-ENTITY_STD_DX, 0);
            }
            break;
            case DIR_RIGHT:
            {
                if(entity->position().x() < (GAME_WIDTH - entity->boundingRect().width()))
                    entity->move(ENTITY_STD_DX, 0);
            }
            break;
            case DIR_UP:
            {
                if(entity->position().y() >= 0)
                    entity->move(0, -ENTITY_STD_DY);
            }
            break;
            case DIR_DOWN:
            {
                if(entity->position().y() < (GAME_HEIGHT - entity->boundingRect().height()))
                    entity->move(0, ENTITY_STD_DY);
            }
            break;
            case DIR_UNKNOWN:
                // do nothing
                break;
        }
        executed_ = true;
        timestamp_ = QTime::currentTime().msecsSinceStartOfDay();
    }
}
