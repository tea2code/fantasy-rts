#include "QuitCommandBuilder.h"

#include <command/QuitCommand.h>


frts::QuitCommandBuilder::QuitCommandBuilder(const IdPtr& commandType)
    : commandType{commandType}
{
}

frts::CommandPtr frts::QuitCommandBuilder::build(const SharedManagerPtr&)
{
    return makeQuitCommand(commandType);
}
