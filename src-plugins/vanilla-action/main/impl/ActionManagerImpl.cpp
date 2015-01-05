#include "ActionManagerImpl.h"

#include <main/ActionIds.h>

#include <frts/vanillacommand>


frts::ActionManagerImpl::ActionManagerImpl()
{

}

void frts::ActionManagerImpl::checkRequiredData(SharedManagerPtr)
{

}

bool frts::ActionManagerImpl::createData(SharedManagerPtr)
{
    return false;
}

void frts::ActionManagerImpl::endAction()
{
    currentAction = nullptr;
    isExecuting = true;
    if (nextAction != nullptr)
    {
        currentAction = nextAction;
        nextAction = nullptr;
    }
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

    // TODO

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

    if (currentAction != nullptr)
    {
        // Set current action to stopping and store new action for laster use..
        nextAction = action;
        stopAction(shared);
    }
    else
    {
        currentAction = action;
    }
}

void frts::ActionManagerImpl::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{

}

bool frts::ActionManagerImpl::preInit(SharedManagerPtr)
{
    isPreInit = true;
    return false;
}

void frts::ActionManagerImpl::stopAction(SharedManagerPtr)
{
    // Stop current action.
    isExecuting = false;
}

void frts::ActionManagerImpl::tick(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    if (currentAction == nullptr)
    {
        return;
    }

    if (isExecuting)
    {
        auto result = currentAction->execute(shared);
        if (result == Action::State::Finished)
        {
            // Action has finished.
            endAction();
        }
        else if (result == Action::State::Cancel)
        {
            // Action wants to cancel.
            isExecuting = false;
        }
    }
    else
    {
        auto result = currentAction->stop(shared);
        if (result != Action::State::Running)
        {
            // Action stopping is finished.
            endAction();
        }
    }
}

void frts::ActionManagerImpl::validateData(SharedManagerPtr)
{

}

void frts::ActionManagerImpl::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
}
