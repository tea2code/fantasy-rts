#include "StopActionOrQuitCommand.h"

#include <main/ActionIds.h>
#include <main/ActionManager.h>

#include <frts/vanillacommand>


frts::StopActionOrQuitCommand::StopActionOrQuitCommand(IdPtr commandType)
    : commandType{commandType}
{

}

frts::StopActionOrQuitCommand::~StopActionOrQuitCommand()
{

}

void frts::StopActionOrQuitCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto actionManager = getUtility<ActionManager>(shared, ActionIds::actionManager());
    bool stoppedAction = actionManager->stopAction(shared);

    if (!stoppedAction)
    {
        auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
        auto quitId = shared->makeId(CommandIds::quit());
        auto quitCommand = commandFactory->makeCommand(quitId, shared);
        quitCommand->execute(shared);
    }
}

frts::IdPtr frts::StopActionOrQuitCommand::getCommandType() const
{
    return commandType;
}

void frts::StopActionOrQuitCommand::undo(SharedManagerPtr)
{
    // No support for undo.
}
