#include "QuitCommandBuilder.h"

#include <command/QuitCommand.h>


frts::QuitCommandBuilder::QuitCommandBuilder()
{
}

frts::CommandPtr frts::QuitCommandBuilder::build(SharedManagerPtr)
{
    return makeQuitCommand();
}
