#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QHash>
#include <QSet>
#include <QSharedPointer>

class Command;
class Entity;
class Game;

//!
//! \brief The CommandFactory class is responsible to process input keys and create commands
//! and register them in the appropriate entity data (component)
//!
class InputHandler final
{
public:
    //!
    //! \brief CommandFactory
    //!
    InputHandler() = default;

    //!
    //! \brief ~CommandFactory
    //!
    ~InputHandler();

    Q_DISABLE_COPY(InputHandler)

    //!
    //! \brief process
    //! \param game
    //! \param entity
    //! \param dt
    //!
    QSharedPointer<Command> process(Qt::Key key);

    //!
    //! \brief bindKeyCommand associate a command within a key
    //! \param key
    //! \param cmd
    //!
    void bind(Qt::Key key, const QSharedPointer<Command> &cmd);

    //!
    //! \brief unbindKeyCommand remove the association between a command and a key
    //! \param key
    //! \return
    //!
    QSharedPointer<Command> unbind(Qt::Key key);

private:

    //!
    //! \brief bindedKeyCommands_ stores the relationship (configuration) between keys and commands
    //!
    QHash<Qt::Key, QSharedPointer<Command>> bindedKeyCommands_;

};

#endif // INPUTHANDLER_H
