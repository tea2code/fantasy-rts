#include "LockableHasResourceManager.h"

#include <entity/HasResource.h>


frts::LockableHasResourceManager::LockableHasResourceManager(
        IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo)
    : componentType{componentType}, resourceManager{distAlgo, region}
{
}

void frts::LockableHasResourceManager::add(EntityPtr entity)
{
    auto component = getComponent<HasResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    for (auto& resourceType : component->getResources())
    {
        resourceManager.add(resourceType, entity);
    }
}

frts::ResourceLockPtr frts::LockableHasResourceManager::findNearest(
        IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared)
{
    return resourceManager.findNearest(entityGroup, resourceType, pos, shared_from_this(), shared);
}

frts::EntityPtr frts::LockableHasResourceManager::getEntity(ResourceLockPtr lock) const
{
    return resourceManager.getEntity(lock);
}

frts::IdPtr frts::LockableHasResourceManager::getResourceType(ResourceLockPtr lock) const
{
    return resourceManager.getResourceType(lock);
}

bool frts::LockableHasResourceManager::isValid(ResourceLockPtr lock) const
{
    return resourceManager.isValid(lock);
}

void frts::LockableHasResourceManager::release(ResourceLockPtr lock)
{
    resourceManager.release(lock);
}

void frts::LockableHasResourceManager::remove(EntityPtr entity)
{
    auto component = getComponent<HasResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    for (auto& resourceType : component->getResources())
    {
        resourceManager.remove(resourceType, entity);
    }
}
