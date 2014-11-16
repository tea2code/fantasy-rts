#include "QuitCommandBuilder.h"

#include <command/QuitCommand.h>


frts::QuitCommandBuilder::QuitCommandBuilder(IdPtr commandType)
    : commandType{commandType}
{
}

frts::CommandPtr frts::QuitCommandBuilder::build(SharedManagerPtr)
{
    return makeQuitCommand(commandType);
}
