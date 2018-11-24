#ifndef SPECIALCOMMAND_H
#define SPECIALCOMMAND_H

#include "command.h"

// fire rate in miliseconds
static const int SPECIAL_COOL_DOWN = 10000;

class Entity;

//!
//! \brief The SpecialCommand class - command executed to start the player special attack
//!
class SpecialCommand : public Command
{
    //Q_OBJECT
//signals:
  //  void coolDownEnd();

public:
    SpecialCommand();
    virtual ~SpecialCommand() override = default;

    Q_DISABLE_COPY(SpecialCommand)

    // Command interface
public:
    void execute(Game *game, QSharedPointer<Entity> entity, int elapsedTime) override;

private:

    //time before the special could be used again
    int cooldown_;

};


#endif // SPECIALCOMMAND_H
