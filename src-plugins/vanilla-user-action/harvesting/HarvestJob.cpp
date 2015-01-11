#include "HarvestJob.h"


frts::HarvestJob::HarvestJob(EntityPtr toHarvest, IdUnorderedSet jobRequirements)
    : jobRequirements{jobRequirements}, toHarvest{toHarvest}
{

}

frts::HarvestJob::~HarvestJob()
{

}

bool frts::HarvestJob::checkSpecialRequirements(EntityPtr entity, SharedManagerPtr shared) const
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    // TODO
    return false;
}

frts::Job::State frts::HarvestJob::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // TODO
    return State::Cancel;
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

    // TODO
    return State::Cancel;
}
