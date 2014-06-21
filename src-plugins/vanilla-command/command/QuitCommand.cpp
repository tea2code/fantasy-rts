#include "QuitCommand.h"


frts::QuitCommand::QuitCommand()
{
}

void frts::QuitCommand::execute(SharedManagerPtr shared)
{
    shared->setQuitApplication(true);
}

void frts::QuitCommand::undo(SharedManagerPtr shared)
{
    shared->setQuitApplication(false);
}
