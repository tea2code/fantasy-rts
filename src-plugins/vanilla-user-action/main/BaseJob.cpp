#include "BaseJob.h"


frts::BaseJob::BaseJob(IdUnorderedSet jobRequirements, EntityPtr jobMarker)
    : dueTime{fromMilliseconds(0)}, jobRequirements{jobRequirements}, jobMarker{jobMarker}
{

}

frts::BaseJob::~BaseJob()
{

}

void frts::BaseJob::clearJobMarker(SharedManagerPtr shared)
{
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    rm->removeEntity(jobMarker, shared);
    jobMarker.reset();
}

frts::Frame::time frts::BaseJob::getDueTime() const
{
    return dueTime;
}

frts::EntityPtr frts::BaseJob::getExecutingEntity() const
{
    return executingEntity;
}

frts::IdUnorderedSet frts::BaseJob::getRequirements() const
{
    return jobRequirements;
}

void frts::BaseJob::setDueTime(Frame::time dueTime)
{
    this->dueTime = dueTime;
}

void frts::BaseJob::setExecutingEntity(EntityPtr entity)
{
    this->executingEntity = entity;
}
