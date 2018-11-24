#include "bombcommand.h"
#include "entity.h"
#include "game.h"

BombCommand::BombCommand() : firerate_(0)
{}

void BombCommand::execute(Game *game, QSharedPointer<Entity> p, int elapsedTime)
{
    firerate_ += elapsedTime;
    if(firerate_ > BOMB_FIRE_RATE)
    {
        if(game != nullptr)
        {
            // drops form the center of the superT model
            game->createPlayerBomb(p->position() + p->boundingRect().center());
        }
        firerate_ = 0;
    }
}
