#include "HarvestJob.h"

#include <frts/vanillamodel>


frts::HarvestJob::HarvestJob(EntityPtr toHarvest, IdUnorderedSet jobRequirements, EntityPtr jobMarker)
    : dueTime{fromMilliseconds(0)}, jobRequirements{jobRequirements}, toHarvest{toHarvest}, jobMarker{jobMarker}
{

}

frts::HarvestJob::~HarvestJob()
{

}

bool frts::HarvestJob::checkSpecialRequirements(EntityPtr entity, SharedManagerPtr shared) const
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    // Is the entity movable?
    if (!entity->hasComponent(shared->makeId(ComponentIds::movable())))
    {
        return false;
    }

    // Does a free neighbor exist?
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto pos = rm->getPos(toHarvest, shared);

    // Null means that toHarvest is already removed. This is handled in the execution so let's just
    // go there.
    if (pos != nullptr)
    {
        auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), entity);
        if(rm->findFreeNeighbors(pos, blockedBy, true, shared).empty())
        {
            return false;
        }
    }

    // Nope everything ok.
    return true;
}

void frts::HarvestJob::clearJobMarker(SharedManagerPtr shared)
{
    // TODO Move into helper function.
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    rm->removeEntity(jobMarker, shared);
    jobMarker.reset();
}

frts::Job::State frts::HarvestJob::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);
    assert(this->harvestState != HarvestJobState::Finished);

    State result = State::Running;

    if (harvestState == HarvestJobState::FirstExecution)
    {
        harvestState = HarvestJobState::Goto;

        // Calculate path.
        // TODO Move into helper function.
        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        auto start = rm->getPos(executingEntity, shared);
        auto pos = rm->getPos(toHarvest, shared);
        if (pos == nullptr)
        {
            // Already harvested?
            result = State::Stop;
        }
        else
        {
            auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), executingEntity);
            auto neighbors = rm->findFreeNeighbors(pos, blockedBy, true, shared);
            if (neighbors.empty())
            {
                result = State::Cancel;
            }
            else
            {
                bool pathFound = false;
                for (auto goal : neighbors)
                {
                    auto path = mf->getPathFinder()->findPath(start, goal, blockedBy, shared);
                    if (!path->pathExists())
                    {
                        continue;
                    }
                    auto movable = getComponent<Movable>(shared->makeId(ComponentIds::movable()), executingEntity);
                    movable->setPath(path);
                    pathFound = true;
                    break;
                }

                if (!pathFound)
                {
                    result = State::Cancel;
                }
            }
        }

        // Not necessary to change due time. Start at the next frame.
    }
    else if (harvestState == HarvestJobState::Goto)
    {
        // TODO Move into helper function.
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        auto movable = getComponent<Movable>(shared->makeId(ComponentIds::movable()), executingEntity);
        auto nextPos = movable->getNextPathPos();
        if (nextPos != nullptr)
        {
            // Move to next position in path.
            rm->setPos(executingEntity, nextPos, shared);

            // Set next due time.
            auto moveTime = fromMilliseconds(1000 / movable->getSpeed());
            dueTime = shared->getFrame()->getRunTime() + moveTime;
        }
        else
        {
            harvestState = HarvestJobState::Harvest;

            if (rm->getPos(toHarvest, shared) == nullptr)
            {
                // Already harvested?
                result = State::Stop;
            }

            // Set next due time.
            // TODO From harvestable component of toHarvest entity.
            dueTime = shared->getFrame()->getRunTime() + fromMilliseconds(333);
        }
    }
    else if (harvestState == HarvestJobState::Harvest)
    {
        harvestState = HarvestJobState::Finished;
        result = State::Finished;

        // Remove toHarvest entity.
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        auto pos = rm->removeEntity(toHarvest, shared);

        // Drop.
        auto dropId = shared->makeId(ComponentIds::drop());
        if (toHarvest->hasComponent(dropId))
        {
            auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
            auto drop = getComponent<Drop>(dropId, toHarvest);
            for (auto dropEntityId : drop->getDrops())
            {
                auto dropEntity = mf->makeEntity(dropEntityId, shared);
                rm->setPos(dropEntity, pos, shared);
            }
        }

        // Remove marker and set to null.
        clearJobMarker(shared);

        // Check if other jobs at this position are still valid.
        // TODO Move into helper function.
        auto jm = getUtility<JobManager>(shared, JobIds::jobManager());
        auto block = rm->getBlock(pos, shared);
        auto jobMarkerId = shared->makeId(JobIds::jobMarker());
        auto otherJobMarkers = block->getByComponent(jobMarkerId);
        for (auto otherJobMarker : otherJobMarkers)
        {
            auto marker = getComponent<JobMarker>(jobMarkerId, otherJobMarker);
            if (!marker->getJob()->isValid(shared))
            {
                jm->stopJob(marker->getJob(), shared);
            }
        }
    }
    // Job was previously stopped but the job manager doesn't know yet.
    else if (harvestState == HarvestJobState::Stopped)
    {
        result = State::Stop;
    }

    return result;
}

frts::Frame::time frts::HarvestJob::getDueTime() const
{
    return dueTime;
}

frts::EntityPtr frts::HarvestJob::getExecutingEntity() const
{
    return executingEntity;
}

frts::IdUnorderedSet frts::HarvestJob::getRequirements() const
{
    return jobRequirements;
}

bool frts::HarvestJob::isValid(SharedManagerPtr shared) const
{
    assert(shared != nullptr);

    // Simple check if the toHarvest entity still exists in the region.
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    return (rm->getPos(toHarvest, shared) != nullptr);
}

void frts::HarvestJob::setExecutingEntity(EntityPtr entity)
{
    this->executingEntity = entity;
}

frts::Job::State frts::HarvestJob::stop(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    if (harvestState != HarvestJobState::Stopped &&
        harvestState != HarvestJobState::Finished)
    {
        // Remove marker and set to null.
        clearJobMarker(shared);
    }

    harvestState = HarvestJobState::Stopped;
    return State::Finished;
}
