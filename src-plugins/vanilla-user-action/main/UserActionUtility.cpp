#include "UserActionUtility.h"

#include <frts/vanillajob>
#include <frts/math.h>


void frts::areJobsValid(const PointPtr& pos, const SharedManagerPtr& shared)
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

void frts::createDrops(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared)
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

bool frts::findPathToJob(const EntityPtr& entity, const PointPtr& jobPos, bool toNeighbor, const SharedManagerPtr& shared)
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

bool frts::moveEntity(const EntityPtr& entity, Frame::time& nextMoveTime, const SharedManagerPtr& shared)
{
    bool result = false;

    auto movable = getComponent<Movable>(shared->makeId(ComponentIds::movable()), entity);
    if (movable != nullptr)
    {
        auto nextPos = movable->getNextPathPos();
        if (nextPos != nullptr)
        {
            // Move to next position in path.
            auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
            rm->setPos(entity, nextPos, shared);

            // Set next due time.
            nextMoveTime = fromMilliseconds(round<unsigned int>(1000.0 / movable->getSpeed()));

            result = true;
        }
    }

    return result;
}
