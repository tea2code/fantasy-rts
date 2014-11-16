#include "QuitCommand.h"


frts::QuitCommand::QuitCommand(IdPtr commandType)
    : commandType{commandType}
{
}

void frts::QuitCommand::execute(SharedManagerPtr shared)
{
    shared->setQuitApplication(true);
}

frts::IdPtr frts::QuitCommand::getCommandType() const
{
    return commandType;
}

void frts::QuitCommand::undo(SharedManagerPtr shared)
{
    shared->setQuitApplication(false);
}
