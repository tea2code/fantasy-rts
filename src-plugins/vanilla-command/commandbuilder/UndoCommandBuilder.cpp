#include "UndoCommandBuilder.h"

#include <command/UndoCommand.h>


frts::UndoCommandBuilder::UndoCommandBuilder(IdPtr commandType)
    : commandType{commandType}
{
}

frts::CommandPtr frts::UndoCommandBuilder::build(SharedManagerPtr)
{
    return makeUndoCommand(commandType);
}
