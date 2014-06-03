#include "LockableIsResourceManagerImpl.h"

#include <entity/IsResource.h>


frts::LockableIsResourceManagerImpl::LockableIsResourceManagerImpl(
        IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo)
    : componentType{componentType}, resourceManager{distAlgo, region}
{
}

void frts::LockableIsResourceManagerImpl::add(EntityPtr entity)
{
    IsResourcePtr component = getComponent<IsResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    resourceManager.add(component->getResourceType(), entity);
}

frts::ResourceLockPtr frts::LockableIsResourceManagerImpl::findNearest(
        IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return resourceManager.findNearest(entityGroup, resourceType, pos, shared_from_this());
}

frts::EntityPtr frts::LockableIsResourceManagerImpl::getEntity(ResourceLockPtr lock) const
{
    return resourceManager.getEntity(lock);
}

frts::IdPtr frts::LockableIsResourceManagerImpl::getResourceType(ResourceLockPtr lock) const
{
    return resourceManager.getResourceType(lock);
}

bool frts::LockableIsResourceManagerImpl::isValid(ResourceLockPtr lock) const
{
    return resourceManager.isValid(lock);
}

void frts::LockableIsResourceManagerImpl::release(ResourceLockPtr lock)
{
    resourceManager.release(lock);
}

void frts::LockableIsResourceManagerImpl::remove(EntityPtr entity)
{
    IsResourcePtr component = getComponent<IsResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    resourceManager.remove(component->getResourceType(), entity);
}
