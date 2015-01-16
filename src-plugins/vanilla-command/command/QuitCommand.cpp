#include "QuitCommand.h"


frts::QuitCommand::QuitCommand(const IdPtr& commandType)
    : commandType{commandType}
{
}

void frts::QuitCommand::execute(const SharedManagerPtr& shared)
{
    shared->setQuitApplication(true);
}

frts::IdPtr frts::QuitCommand::getCommandType() const
{
    return commandType;
}

void frts::QuitCommand::undo(const SharedManagerPtr& shared)
{
    shared->setQuitApplication(false);
}
