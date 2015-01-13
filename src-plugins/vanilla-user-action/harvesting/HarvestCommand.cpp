#include "HarvestCommand.h"

#include "HarvestAction.h"

#include <frts/configuration>

#include <boost/format.hpp>


frts::HarvestCommand::HarvestCommand(IdPtr commandType, IdPtr userActionType, ConfigNodePtr settings)
    : commandType{commandType}, userActionType{userActionType}, settings{settings}
{

}

frts::HarvestCommand::~HarvestCommand()
{

}

void frts::HarvestCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // Parse settings.
    IdUnorderedSet harvestTypes;
    for (auto& harvestType : settings->getStrings("harvest_types"))
    {
        harvestTypes.insert(shared->makeId(harvestType));
    }
    if (harvestTypes.empty())
    {
        auto msg = boost::format(R"(%1%: No harvest types defined for command "%2%".")")
                % name % commandType->toString();
        throw DataViolation(msg.str());
    }

    IdPtr jobMarker = shared->makeId(settings->getString("jobmarker"));

    IdUnorderedSet jobRequirements;
    for (auto& jobRequirement : settings->getStrings("requirements"))
    {
        jobRequirements.insert(shared->makeId(jobRequirement));
    }

    // Create and start action.
    action = makeHarvestAction(commandType, userActionType, harvestTypes, jobRequirements, jobMarker);
    auto am = getUtility<ActionManager>(shared, ActionIds::actionManager());
    am->newAction(action, shared);
}

frts::IdPtr frts::HarvestCommand::getCommandType() const
{
    return commandType;
}

void frts::HarvestCommand::undo(SharedManagerPtr shared)
{
    assert(shared != nullptr);
    assert(this->action != nullptr);

    action->stop(shared);
}
