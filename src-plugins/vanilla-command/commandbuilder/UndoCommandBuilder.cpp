#include "UndoCommandBuilder.h"

#include <command/UndoCommand.h>


frts::UndoCommandBuilder::UndoCommandBuilder(const IdPtr& commandType)
    : commandType{commandType}
{
}

frts::CommandPtr frts::UndoCommandBuilder::build(const SharedManagerPtr&)
{
    return makeUndoCommand(commandType);
}
