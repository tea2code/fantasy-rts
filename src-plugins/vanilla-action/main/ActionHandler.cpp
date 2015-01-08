#include "ActionHandler.h"

#include "ActionIds.h"


frts::ActionHandler::ActionHandler()
    : BaseTickable(ActionIds::actionHandler(), 1, ActionIds::actionHandler(), 1)
{

}

frts::ActionHandler::~ActionHandler()
{

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
