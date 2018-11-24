#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "command.h"

//!
//! \brief The DIRECTION enum movement direction for command
//!
enum DIRECTION {
    DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_UNKNOWN
};

//!
//! \brief The MoveCommand class
//!
class MoveCommand : public Command
{
public:
    //!
    //! \brief MoveCommand
    //! \param dir
    //!
    MoveCommand(DIRECTION dir);
    //!
    virtual ~MoveCommand() override = default;

    Q_DISABLE_COPY(MoveCommand)

    // Command interface
    //!
    //! \brief execute
    //! \param world
    //! \param entity
    //! \param elapsedTime
    //!
    void execute(Game* game, QSharedPointer<Entity> entity, int elapsedTime) override;

private:

    DIRECTION dir_;

};

#endif // MOVECOMMAND_H
