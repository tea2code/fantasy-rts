#include "LockableIsResourceManager.h"

#include <entity/IsResource.h>


frts::LockableIsResourceManager::LockableIsResourceManager(
        IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo)
    : componentType{componentType}, resourceManager{distAlgo, region}
{
}

void frts::LockableIsResourceManager::add(EntityPtr entity)
{
    auto component = getComponent<IsResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    resourceManager.add(component->getResourceType(), entity);
}

frts::ResourceLockPtr frts::LockableIsResourceManager::findNearest(
        IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return resourceManager.findNearest(entityGroup, resourceType, pos, shared_from_this());
}

frts::EntityPtr frts::LockableIsResourceManager::getEntity(ResourceLockPtr lock) const
{
    return resourceManager.getEntity(lock);
}

frts::IdPtr frts::LockableIsResourceManager::getResourceType(ResourceLockPtr lock) const
{
    return resourceManager.getResourceType(lock);
}

bool frts::LockableIsResourceManager::isValid(ResourceLockPtr lock) const
{
    return resourceManager.isValid(lock);
}

void frts::LockableIsResourceManager::release(ResourceLockPtr lock)
{
    resourceManager.release(lock);
}

void frts::LockableIsResourceManager::remove(EntityPtr entity)
{
    auto component = getComponent<IsResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    resourceManager.remove(component->getResourceType(), entity);
}
