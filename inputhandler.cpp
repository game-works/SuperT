#include "inputhandler.h"

#include "command.h"

InputHandler::~InputHandler()
{
    bindedKeyCommands_.clear();
}


QSharedPointer<Command> InputHandler::process(Qt::Key key)
{
    QSharedPointer<Command> cmd = bindedKeyCommands_.value(key, nullptr);
    return cmd;
}

void InputHandler::bind(Qt::Key key, const QSharedPointer<Command>& cmd)
{
    bindedKeyCommands_.insert(key, cmd);
}

QSharedPointer<Command> InputHandler::unbind(Qt::Key key)
{
    return bindedKeyCommands_.take(key);
}

