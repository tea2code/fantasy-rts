#include "CarveCommand.h"

//#include "CarveAction.h"

#include <frts/configuration>

#include <boost/format.hpp>


frts::CarveCommand::CarveCommand(const IdPtr& commandType, const IdPtr& userActionType, const ConfigNodePtr& settings)
    : commandType{commandType}, userActionType{userActionType}, settings{settings}
{

}

frts::CarveCommand::~CarveCommand()
{

}

void frts::CarveCommand::execute(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    shared->getLog()->debug(name, "execute");

//    // Parse settings.
//    IdUnorderedSet harvestTypes;
//    for (auto& harvestType : settings->getStrings("harvest_types"))
//    {
//        harvestTypes.insert(shared->makeId(harvestType));
//    }
//    if (harvestTypes.empty())
//    {
//        auto msg = boost::format(R"(%1%: No harvest types defined for command "%2%".")")
//                % name % commandType->toString();
//        throw DataViolation(msg.str());
//    }

//    IdPtr jobMarker = shared->makeId(settings->getString("jobmarker"));

//    IdUnorderedSet jobRequirements;
//    for (auto& jobRequirement : settings->getStrings("requirements"))
//    {
//        jobRequirements.insert(shared->makeId(jobRequirement));
//    }

    // Create and start action.
//    action = makeHarvestAction(commandType, userActionType, harvestTypes, jobRequirements, jobMarker);
//    auto am = getUtility<ActionManager>(shared, ActionIds::actionManager());
//    am->newAction(action, shared);
}

frts::IdPtr frts::CarveCommand::getCommandType() const
{
    return commandType;
}

void frts::CarveCommand::undo(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);
    assert(this->action != nullptr);

    action->stop(shared);
}
