#include "BaseJob.h"


frts::BaseJob::BaseJob(const IdPtr& id, const IdPtr& type, const IdUnorderedSet& jobRequirements, const EntityPtr& jobMarker)
    : dueTime{fromMilliseconds(0)}, id{id}, jobRequirements{jobRequirements},
      type{type}, jobMarker{jobMarker}
{

}

frts::BaseJob::~BaseJob()
{

}

void frts::BaseJob::clearJobMarker(const SharedManagerPtr& shared)
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

frts::IdPtr frts::BaseJob::getId() const
{
    return id;
}

frts::IdUnorderedSet frts::BaseJob::getRequirements() const
{
    return jobRequirements;
}

frts::IdPtr frts::BaseJob::getType() const
{
    return type;
}

void frts::BaseJob::setDueTime(Frame::time dueTime)
{
    this->dueTime = dueTime;
}

void frts::BaseJob::setExecutingEntity(const EntityPtr& entity)
{
    this->executingEntity = entity;
}
