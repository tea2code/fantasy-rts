#include "UserActionFactoryImpl.h"

#include <main/UserActionIds.h>
#include <harvesting/HarvestCommandBuilder.h>
#include <special/stop-jobs/StopJobsCommandBuilder.h>

#include <frts/vanillaaction>
#include <frts/vanillacommand>
#include <frts/vanillajob>
#include <frts/vanillamodel>

#include <boost/format.hpp>


frts::UserActionFactoryImpl::UserActionFactoryImpl()
    : BaseUtility(UserActionIds::userActionFactory(), 1, UserActionIds::userActionFactory(), 1)
{

}

frts::UserActionFactoryImpl::~UserActionFactoryImpl()
{

}

void frts::UserActionFactoryImpl::createDrops(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    auto dropId = shared->makeId(ComponentIds::drop());
    if (entity->hasComponent(dropId))
    {
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

        auto drop = getComponent<Drop>(dropId, entity);
        for (auto& dropEntityId : drop->getDrops())
        {
            auto dropEntity = mf->makeEntity(dropEntityId, shared);
            rm->setPos(dropEntity, pos, shared);
        }
    }
}

void frts::UserActionFactoryImpl::confirmJobsValidOrStop(const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto jm = getUtility<JobManager>(shared, JobIds::jobManager());

    auto block = rm->getBlock(pos, shared);
    auto jobMarkerId = shared->makeId(JobIds::jobMarker());
    auto otherJobMarkers = block->getByComponent(jobMarkerId);
    for (auto& otherJobMarker : otherJobMarkers)
    {
        auto marker = getComponent<JobMarker>(jobMarkerId, otherJobMarker);
        if (!marker->getJob()->isValid(shared))
        {
            jm->stopJob(marker->getJob(), shared);
        }
    }
}

bool frts::UserActionFactoryImpl::findPathToJob(const EntityPtr& entity, const PointPtr& jobPos,
                                                bool toNeighbor, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(jobPos != nullptr);
    assert(shared != nullptr);

    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    // Get entity properties.
    auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), entity);
    auto start = rm->getPos(entity, shared);

    // Get goals.
    PointVector goals;
    if (toNeighbor)
    {
        goals = rm->findFreeNeighbors(jobPos, blockedBy, true, shared);

        // Sort by distance to have a more believable movement pattern for units.
        auto distAlgo = mf->getDistanceAlgorithm();
        auto distCompare = [&](const PointPtr& pos1, const PointPtr& pos2)
        {
            return distAlgo->distance(start, pos1) < distAlgo->distance(start, pos2);
        };
        std::sort(goals.begin(), goals.end(), distCompare);
    }
    else
    {
        goals.push_back(jobPos);
    }
    if (goals.empty())
    {
        return false;
    }

    // Try to find path for given unit.
    bool pathFound = false;
    for (auto& goal : goals)
    {
        auto path = mf->getPathFinder()->findPath(start, goal, blockedBy, shared);
        if (!path->pathExists())
        {
            continue;
        }
        auto movable = getComponent<Movable>(shared->makeId(ComponentIds::movable()), entity);
        movable->setPath(path);
        pathFound = true;
        break;
    }

    return pathFound;
}

std::vector<std::string> frts::UserActionFactoryImpl::getSupportedConfig()
{
    return {"useraction"};
}

bool frts::UserActionFactoryImpl::init(const SharedManagerPtr& shared)
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

frts::UserActionFactory::MoveEntityResult frts::UserActionFactoryImpl::moveEntity(const EntityPtr& entity,
                                                                                  const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    MoveEntityResult result;
    result.state = MoveEntityResult::NotMovable;

    auto movable = getComponent<Movable>(shared->makeId(ComponentIds::movable()), entity);
    if (movable != nullptr)
    {
        auto nextPos = movable->getNextPathPos();
        if (nextPos != nullptr)
        {
            auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

            // Check if path is blocked.
            auto block = rm->getBlock(nextPos, shared);
            auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), entity);
            if (block->isBlocking(blockedBy))
            {
                result.state = MoveEntityResult::Blocked;
            }
            else
            {
                // Move to next position in path.
                rm->setPos(entity, nextPos, shared);

                result.nextMoveTime = fromMilliseconds(round<unsigned int>(1000.0 / movable->getSpeed()));
                result.state = MoveEntityResult::Moved;
            }
        }
        else
        {
            result.state = MoveEntityResult::AtTarget;
        }
    }

    return result;
}

void frts::UserActionFactoryImpl::parseConfig(const std::string&, const ConfigNodePtr& node, const SharedManagerPtr& shared)
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

void frts::UserActionFactoryImpl::validateModules(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ActionIds::actionManager(), 1, shared);
    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
    validateUtility(getName(), JobIds::jobManager(), 3, shared);
    validateUtility(getName(), ModelIds::modelFactory(), 2, shared);
}
