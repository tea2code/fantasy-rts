#include "ActionManagerImpl.h"

#include "StopActionCommandBuilder.h"
#include "StopActionOrQuitCommandBuilder.h"
#include <main/ActionIds.h>

#include <frts/vanillacommand>


frts::ActionManagerImpl::ActionManagerImpl(const ActionHandlerPtr& actionHandler)
    : BaseUtility(ActionIds::actionManager(), 1, ActionIds::actionManager(), 1),
      actionHandler{actionHandler}
{

}

bool frts::ActionManagerImpl::init(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());

    auto commandId = shared->makeId(ActionIds::stopActionCommand());
    auto builder = makeStopActionCommandBuilder(commandId);
    commandFactory->registerCommandBuilder(commandId, builder);

    commandId = shared->makeId(ActionIds::stopActionOrQuitCommand());
    builder = makeStopActionOrQuitCommandBuilder(commandId);
    commandFactory->registerCommandBuilder(commandId, builder);

    return BaseUtility::init(shared);
}

void frts::ActionManagerImpl::newAction(const ActionPtr& action, const SharedManagerPtr& shared)
{
    assert(action != nullptr);
    assert(shared != nullptr);

    actionHandler->newAction(action, shared);
}

bool frts::ActionManagerImpl::stopAction(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    return actionHandler->stopAction(shared);
}

void frts::ActionManagerImpl::validateModules(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateTickable(getName(), ActionIds::actionHandler(), 1, shared);
    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
}
