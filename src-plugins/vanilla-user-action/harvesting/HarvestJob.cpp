#include "HarvestJob.h"

#include <main/UserActionUtility.h>
#include <frts/vanillamodel>
#include <frts/math.h>

#include <algorithm>


frts::HarvestJob::HarvestJob(const IdPtr& id, const IdPtr& type, const EntityPtr& toHarvest, const IdUnorderedSet& jobRequirements, const EntityPtr& jobMarker)
    : BaseJob(id, type, jobRequirements, jobMarker), toHarvest{toHarvest}
{

}

frts::HarvestJob::~HarvestJob()
{

}

bool frts::HarvestJob::checkSpecialRequirements(const EntityPtr& entity, const SharedManagerPtr& shared) const
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

frts::Job::State frts::HarvestJob::execute(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);
    assert(this->jobState != JobState::Finished);

    State result = State::Running;

    if (jobState == JobState::FirstExecution)
    {
        jobState = JobState::Goto;

        // Calculate path.
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        auto pos = rm->getPos(toHarvest, shared);

        // Already harvested?
        if (pos == nullptr)
        {
            result = State::Stop;
        }
        else
        {
            // Find a path to one of the neighbors of the job position.
            bool pathFound = findPathToJob(getExecutingEntity(), pos, true, shared);
            if (!pathFound)
            {
                result = State::Cancel;
            }
        }

        // Not necessary to change due time. Start at the next frame.
    }
    else if (jobState == JobState::Goto)
    {
        // Already harvested?
        if (!isValid(shared))
        {
            result = State::Stop;
        }

        Frame::time moveTime;
        bool moved = moveEntity(getExecutingEntity(), moveTime, shared);
        if (moved)
        {
            // Set next due time.
            setDueTime(shared->getFrame()->getRunTime() + moveTime);
        }
        else
        {
            jobState = JobState::Harvest;

            // Set next due time.
            auto harvestable = getComponent<Harvestable>(shared->makeId(ComponentIds::harvestable()), toHarvest);
            auto harvestTime = fromMilliseconds(round<unsigned int>(1000.0 / harvestable->getSpeed()));
            setDueTime(shared->getFrame()->getRunTime() + harvestTime);
        }
    }
    else if (jobState == JobState::Harvest)
    {
        jobState = JobState::Finished;
        result = State::Finished;

        // Remove toHarvest entity.
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        auto pos = rm->removeEntity(toHarvest, shared);

        // Already harvested?
        if (pos == nullptr)
        {
            result = State::Stop;
        }
        else
        {
            // Drops.
            createDrops(toHarvest, pos, shared);
        }

        // Remove marker and set to null.
        clearJobMarker(shared);

        // Check if other jobs at this position are still valid.
        if (pos != nullptr)
        {
            areJobsValid(pos, shared);
        }
    }
    // Job was previously stopped but the job manager doesn't know yet.
    else if (jobState == JobState::Stopped)
    {
        result = State::Stop;
    }

    return result;
}

bool frts::HarvestJob::isValid(const SharedManagerPtr& shared) const
{
    assert(shared != nullptr);

    // Simple check if the toHarvest entity still exists in the region.
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    return (rm->getPos(toHarvest, shared) != nullptr);
}

frts::Job::State frts::HarvestJob::stop(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    if (jobState != JobState::Stopped &&
        jobState != JobState::Finished)
    {
        // Remove marker and set to null.
        clearJobMarker(shared);
    }

    jobState = JobState::Stopped;
    return State::Finished;
}
