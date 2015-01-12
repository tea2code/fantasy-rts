#include "HarvestJob.h"

#include <frts/vanillamodel>


frts::HarvestJob::HarvestJob(EntityPtr toHarvest, IdUnorderedSet jobRequirements, EntityPtr jobMarker)
    : jobRequirements{jobRequirements}, toHarvest{toHarvest}, jobMarker{jobMarker}
{

}

frts::HarvestJob::~HarvestJob()
{

}

bool frts::HarvestJob::checkSpecialRequirements(EntityPtr entity, SharedManagerPtr shared) const
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    // Currently only a check if a free neighbor exists is made. Everything else happens during
    // job execution.
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto pos = rm->getPos(toHarvest, shared);
    auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), entity);
    return !rm->findFreeNeighbors(pos, blockedBy, true, shared).empty();
}

void frts::HarvestJob::clearJobMarker(SharedManagerPtr shared)
{
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    rm->removeEntity(jobMarker, shared);
    jobMarker.reset();
}

frts::Job::State frts::HarvestJob::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);
    assert(this->harvestState != HarvestJobState::Finished);

    clearJobMarker(shared);
    return State::Finished;

    State result = State::Running;

    if (harvestState == HarvestJobState::FirstExecution)
    {
        harvestState = HarvestJobState::Goto;

        // TODO Calculate path.
        // TODO Set next due time.
    }
    else if (harvestState == HarvestJobState::Goto)
    {
        if (true /* not yet at target */)
        {
            // TODO Move to next position in path.
            // TODO Set next due time.
        }
        else
        {
            harvestState = HarvestJobState::Harvest;

            // TODO Set next due time.
        }
    }
    else if (harvestState == HarvestJobState::Harvest)
    {
        harvestState = HarvestJobState::Finished;
        result = State::Finished;

        // TODO Remove toHarvest entity.
        // TODO Drop

        // Remove marker and set to null.
        clearJobMarker(shared);
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
    return fromMilliseconds(0);
}

frts::EntityPtr frts::HarvestJob::getExecutingEntity() const
{
    return executingEntity;
}

frts::IdUnorderedSet frts::HarvestJob::getRequirements() const
{
    return jobRequirements;
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
