#include "shotcommand.h"
#include "entity.h"
#include "game.h"

ShotCommand::ShotCommand() : framerate_(0)
{}

void ShotCommand::execute(Game *game, QSharedPointer<Entity> p, int elapsedTime)
{
    framerate_ += elapsedTime;
    if(framerate_ > FIRE_RATE)
    {
        if(game != nullptr)
        {
            game->createPlayerShoot(p->position() + p->boundingRect().center());
        }
        framerate_ = 0;
    }
}
