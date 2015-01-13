#include "StopJobsCommand.h"

#include "StopJobsAction.h"


frts::StopJobsCommand::StopJobsCommand(IdPtr commandType, ConfigNodePtr settings)
    : commandType{commandType}, settings{settings}
{

}

frts::StopJobsCommand::~StopJobsCommand()
{

}

void frts::StopJobsCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // Parse settings.
    IdUnorderedSet jobs;
    if (settings->has("jobs"))
    {
        for (auto& id : settings->getStrings("jobs"))
        {
            jobs.insert(shared->makeId(id));
        }
    }

    IdUnorderedSet types;
    if (settings->has("types"))
    {
        for (auto& id : settings->getStrings("types"))
        {
            types.insert(shared->makeId(id));
        }
    }

    // Create and start action.
    action = makeStopJobsAction(jobs, types);
    auto am = getUtility<ActionManager>(shared, ActionIds::actionManager());
    am->newAction(action, shared);
}

frts::IdPtr frts::StopJobsCommand::getCommandType() const
{
    return commandType;
}

void frts::StopJobsCommand::undo(SharedManagerPtr shared)
{
    assert(shared != nullptr);
    assert(this->action != nullptr);

    action->stop(shared);
}
