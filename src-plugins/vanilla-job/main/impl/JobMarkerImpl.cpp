#include "JobMarkerImpl.h"


frts::JobMarkerImpl::JobMarkerImpl(IdPtr componentType)
    : componentType{componentType}
{

}

frts::JobMarkerImpl::~JobMarkerImpl()
{

}

frts::IdPtr frts::JobMarkerImpl::getComponentType() const
{
    return componentType;
}

frts::JobPtr frts::JobMarkerImpl::getJob() const
{
    return job;
}

void frts::JobMarkerImpl::setJob(JobPtr job)
{
    assert(job != nullptr);

    this->job = job;
}
