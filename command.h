#ifndef COMMAND_H
#define COMMAND_H

#include <QSharedPointer>

class Entity;
class Game;

//!
//! \brief The Command class
//!
class Command
{
public:
    //!
    //! \brief Command
    //!
    Command() : timestamp_(0), executed_(false) { }

    //!
    //! \brief ~Command
    //!
    virtual ~Command() {}

    Q_DISABLE_COPY(Command)

    //!
    //! \brief execute
    //! \param entity
    //! \param elapsedTime
    //!
    virtual void execute(Game* game, QSharedPointer<Entity> entity, int elapsedTime) = 0;

    inline int timestamp() const { return timestamp_; }

    inline bool executed() const { return executed_; }

    void setTimestamp(int timestamp) { timestamp_ = timestamp; }

    void setExecuted(bool executed) { executed_ = executed; }

protected:

    //!
    //! \brief timestamp_ the time in ms when command was created,
    //!
    int timestamp_;

    //!
    //! \brief executed_ a flag to indicate if the command was already processed
    //!
    bool executed_;

};

#endif // COMMAND_H




