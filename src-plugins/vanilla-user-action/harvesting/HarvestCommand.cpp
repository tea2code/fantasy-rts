#include "HarvestCommand.h"

#include "HarvestAction.h"

#include <frts/configuration>

#include <boost/format.hpp>


frts::HarvestCommand::HarvestCommand(IdPtr commandType, ConfigNodePtr settings)
    : commandType{commandType}, settings{settings}
{

}

frts::HarvestCommand::~HarvestCommand()
{

}

void frts::HarvestCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    shared->getLog()->debug(name, "execute");

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

    IdUnorderedSet jobRequirements;
    for (auto& jobRequirement : settings->getStrings("requirements"))
    {
        jobRequirements.insert(shared->makeId(jobRequirement));
    }

    // Create and start action.
    action = makeHarvestAction(harvestTypes, jobRequirements);
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

    shared->getLog()->debug(name, "stop");

    action->stop(shared);
}
