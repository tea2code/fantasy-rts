#include "ActionHandler.h"


frts::ActionHandler::ActionHandler()
{

}

frts::ActionHandler::~ActionHandler()
{

}

void frts::ActionHandler::checkRequiredData(SharedManagerPtr)
{

}

bool frts::ActionHandler::createData(SharedManagerPtr)
{
    return false;
}

void frts::ActionHandler::endAction()
{
    currentAction = nullptr;
    isExecuting = true;
    if (nextAction != nullptr)
    {
        currentAction = nextAction;
        nextAction = nullptr;
    }
}

std::string frts::ActionHandler::getName() const
{
    return "frts::ActionHandler";
}

std::vector<std::string> frts::ActionHandler::getSupportedConfig()
{
    return {};
}

std::string frts::ActionHandler::getTypeName() const
{
    return getName();
}

int frts::ActionHandler::getTypeVersion() const
{
    return getVersion();
}

int frts::ActionHandler::getVersion() const
{
    return 1;
}

bool frts::ActionHandler::init(SharedManagerPtr)
{
    isInit = true;
    return false;
}

bool frts::ActionHandler::isInitialized() const
{
    return isInit;
}

bool frts::ActionHandler::isPreInitialized() const
{
    return isPreInit;
}

void frts::ActionHandler::newAction(ActionPtr action, SharedManagerPtr shared)
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

void frts::ActionHandler::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{

}

bool frts::ActionHandler::preInit(SharedManagerPtr)
{
    isPreInit = true;
    return false;
}

bool frts::ActionHandler::stopAction(SharedManagerPtr)
{
    if (currentAction != nullptr)
    {
        // Stop current action.
        isExecuting = false;
    }

    return (currentAction != nullptr);
}

void frts::ActionHandler::tick(SharedManagerPtr shared)
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

void frts::ActionHandler::validateData(SharedManagerPtr)
{

}

void frts::ActionHandler::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);
}
