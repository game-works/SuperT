#ifndef SHOTCOMMAND_H
#define SHOTCOMMAND_H

#include "command.h"

class Entity;

static const int FIRE_RATE = 100; // miliseconds interval

//!
//! \brief The ShotCommand class - player shot command
//!]
class ShotCommand : public Command
{
public:
    ShotCommand();
    virtual ~ShotCommand() override = default;

    Q_DISABLE_COPY(ShotCommand)

    // Command interface
public:
    void execute(Game *game, QSharedPointer<Entity> e, int elapsedTime) override;

private:

    int framerate_;
};

#endif // SHOOTCOMMAND_H
