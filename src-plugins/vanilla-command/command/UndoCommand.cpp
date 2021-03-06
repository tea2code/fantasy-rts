#include "UndoCommand.h"

#include <main/CommandFactory.h>
#include <main/CommandIds.h>


frts::UndoCommand::UndoCommand(const IdPtr& commandType)
    : commandType{commandType}
{
}

void frts::UndoCommand::execute(const SharedManagerPtr& shared)
{
    getUtility<CommandFactory>(shared, CommandIds::commandFactory())->undoLastCommand(shared);
}

frts::IdPtr frts::UndoCommand::getCommandType() const
{
    return commandType;
}

void frts::UndoCommand::undo(const SharedManagerPtr&)
{
    // Nope, no undo undo. Cause undoception will create a singularity.
    // And ain't nobody got time for this.
}
