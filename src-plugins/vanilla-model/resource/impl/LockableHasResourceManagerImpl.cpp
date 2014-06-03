#include "LockableHasResourceManagerImpl.h"

#include <entity/HasResource.h>


frts::LockableHasResourceManagerImpl::LockableHasResourceManagerImpl(
        IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo)
    : componentType{componentType}, resourceManager{distAlgo, region}
{
}

void frts::LockableHasResourceManagerImpl::add(EntityPtr entity)
{
    HasResourcePtr component = getComponent<HasResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    for (auto resourceType : component->getResources())
    {
        resourceManager.add(resourceType, entity);
    }
}

frts::ResourceLockPtr frts::LockableHasResourceManagerImpl::findNearest(
        IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return resourceManager.findNearest(entityGroup, resourceType, pos, shared_from_this());
}

frts::EntityPtr frts::LockableHasResourceManagerImpl::getEntity(ResourceLockPtr lock) const
{
    return resourceManager.getEntity(lock);
}

frts::IdPtr frts::LockableHasResourceManagerImpl::getResourceType(ResourceLockPtr lock) const
{
    return resourceManager.getResourceType(lock);
}

bool frts::LockableHasResourceManagerImpl::isValid(ResourceLockPtr lock) const
{
    return resourceManager.isValid(lock);
}

void frts::LockableHasResourceManagerImpl::release(ResourceLockPtr lock)
{
    resourceManager.release(lock);
}

void frts::LockableHasResourceManagerImpl::remove(EntityPtr entity)
{
    HasResourcePtr component = getComponent<HasResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    for (auto resourceType : component->getResources())
    {
        resourceManager.remove(resourceType, entity);
    }
}
