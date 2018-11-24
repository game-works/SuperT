#ifndef BOMBCOMMAND_H
#define BOMBCOMMAND_H

#include "command.h"

// fire rate in miliseconds
static const int BOMB_FIRE_RATE = 200;

class Entity;

//!
//! \brief The BombCommand class - command executed to add a player bomb to the scene
//!
class BombCommand : public Command
{
public:
    BombCommand();
    virtual ~BombCommand() override = default;

    Q_DISABLE_COPY(BombCommand)

    // Command interface
public:
    void execute(Game *game, QSharedPointer<Entity> e, int elapsedTime) override;

private:

    int firerate_;
};

#endif // BOMBCOMMAND_H
