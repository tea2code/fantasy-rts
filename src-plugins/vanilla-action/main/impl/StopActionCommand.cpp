#include "StopActionCommand.h"

#include <main/ActionIds.h>
#include <main/ActionManager.h>


frts::StopActionCommand::StopActionCommand(const IdPtr& commandType)
    : commandType{commandType}
{

}

frts::StopActionCommand::~StopActionCommand()
{

}

void frts::StopActionCommand::execute(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto actionManager = getUtility<ActionManager>(shared, ActionIds::actionManager());
    actionManager->stopAction(shared);
}

frts::IdPtr frts::StopActionCommand::getCommandType() const
{
    return commandType;
}

void frts::StopActionCommand::undo(const SharedManagerPtr&)
{
    // No support for undo.
}
