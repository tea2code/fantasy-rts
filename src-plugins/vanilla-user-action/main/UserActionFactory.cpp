#include "UserActionFactory.h"

#include "UserActionIds.h"
#include <harvesting/HarvestCommandBuilder.h>
#include <special/stop-jobs/StopJobsCommandBuilder.h>

#include <frts/vanillaaction>
#include <frts/vanillacommand>
#include <frts/vanillajob>
#include <frts/vanillamodel>

#include <boost/format.hpp>


frts::UserActionFactory::UserActionFactory()
    : BaseUtility(UserActionIds::userActionFactory(), 1, UserActionIds::userActionFactory(), 1)
{

}

frts::UserActionFactory::~UserActionFactory()
{

}

std::vector<std::string> frts::UserActionFactory::getSupportedConfig()
{
    return {"useraction"};
}

bool frts::UserActionFactory::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto cf = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
    auto jm = getUtility<JobManager>(shared, JobIds::jobManager());
    auto am = getUtility<ActionManager>(shared, ActionIds::actionManager());

    if (!cf->isInitialized() || !jm->isInitialized() || !am->isInitialized())
    {
        return true;
    }

    for (auto& it : commandConfigs)
    {
        auto commandId = it.first;
        auto config = it.second;
        UserActionCommandBuilderPtr commandBuilder;

        if (config.type->toString() == UserActionIds::harvest())
        {
            commandBuilder = makeHarvestCommandBuilder(commandId, config.type);
        }
        else if (config.type->toString() == UserActionIds::stopJobs())
        {
            commandBuilder = makeStopJobsCommandBuilder(commandId);
        }
        else
        {
            auto msg = boost::format(R"(Unknown user action command of type "%1%".)")
                    % config.type->toString();
            shared->getLog()->warning(getName(), msg.str());
            continue;
        }

        commandBuilder->setSettings(config.settings);
        cf->registerCommandBuilder(commandId, commandBuilder);
    }

    return BaseUtility::init(shared);
}

void frts::UserActionFactory::parseConfig(const std::string&, ConfigNodePtr node, SharedManagerPtr shared)
{
    assert(node != nullptr);
    assert(shared != nullptr);

    std::string ns = node->getString("namespace", "");
    if (!ns.empty())
    {
        ns += ".";
    }

    auto userActions = node->getNode("useractions");
    for (auto userAction : *userActions)
    {
        auto command = shared->makeId(ns + userAction->getString("command"));
        CommandConfig config;
        config.type = shared->makeId(userAction->getString("type"));
        config.settings = userAction->getNode("settings");
        commandConfigs[command] = config;
    }
}

void frts::UserActionFactory::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ActionIds::actionManager(), 1, shared);
    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
    validateUtility(getName(), JobIds::jobManager(), 3, shared);
    validateUtility(getName(), ModelIds::modelFactory(), 2, shared);
}
