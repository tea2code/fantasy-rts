#include "ActionManagerImpl.h"

#include "StopActionCommandBuilder.h"
#include "StopActionOrQuitCommandBuilder.h"
#include <main/ActionIds.h>

#include <frts/vanillacommand>


frts::ActionManagerImpl::ActionManagerImpl(ActionHandlerPtr actionHandler)
    : actionHandler{actionHandler}
{

}

void frts::ActionManagerImpl::checkRequiredData(SharedManagerPtr)
{

}

bool frts::ActionManagerImpl::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::ActionManagerImpl::getName() const
{
    return ActionIds::actionManager();
}

std::vector<std::string> frts::ActionManagerImpl::getSupportedConfig()
{
    return {};
}

std::string frts::ActionManagerImpl::getTypeName() const
{
    return getName();
}

int frts::ActionManagerImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::ActionManagerImpl::getVersion() const
{
    return 1;
}

bool frts::ActionManagerImpl::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());

    auto commandId = shared->makeId(ActionIds::stopActionCommand());
    auto builder = makeStopActionCommandBuilder(commandId);
    commandFactory->registerCommandBuilder(commandId, builder);

    commandId = shared->makeId(ActionIds::stopActionOrQuitCommand());
    builder = makeStopActionOrQuitCommandBuilder(commandId);
    commandFactory->registerCommandBuilder(commandId, builder);

    isInit = true;
    return false;
}

bool frts::ActionManagerImpl::isInitialized() const
{
    return isInit;
}

bool frts::ActionManagerImpl::isPreInitialized() const
{
    return isPreInit;
}

void frts::ActionManagerImpl::newAction(ActionPtr action, SharedManagerPtr shared)
{
    assert(action != nullptr);
    assert(shared != nullptr);

    actionHandler->newAction(action, shared);
}

void frts::ActionManagerImpl::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{

}

bool frts::ActionManagerImpl::preInit(SharedManagerPtr)
{
    isPreInit = true;
    return false;
}

bool frts::ActionManagerImpl::stopAction(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    return actionHandler->stopAction(shared);
}

void frts::ActionManagerImpl::validateData(SharedManagerPtr)
{

}

void frts::ActionManagerImpl::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateTickable(getName(), ActionIds::actionHandler(), 1, shared);
    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
}
