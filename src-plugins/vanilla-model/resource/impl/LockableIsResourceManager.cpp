#include "LockableIsResourceManager.h"

#include <entity/IsResource.h>


frts::LockableIsResourceManager::LockableIsResourceManager(
        IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo)
    : componentType{componentType}, resourceManager{distAlgo, region}
{
}

void frts::LockableIsResourceManager::add(EntityPtr entity)
{
    assert(entity != nullptr);

    auto component = getComponent<IsResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    resourceManager.add(component->getResourceType(), entity);
}

frts::ResourceLockPtr frts::LockableIsResourceManager::findNearest(
        IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    return resourceManager.findNearest(entityGroup, resourceType, pos, shared_from_this(), shared);
}

frts::EntityPtr frts::LockableIsResourceManager::getEntity(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    return resourceManager.getEntity(lock);
}

frts::IdPtr frts::LockableIsResourceManager::getResourceType(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    return resourceManager.getResourceType(lock);
}

bool frts::LockableIsResourceManager::isValid(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    return resourceManager.isValid(lock);
}

void frts::LockableIsResourceManager::release(ResourceLockPtr lock)
{
    assert(lock != nullptr);

    resourceManager.release(lock);
}

void frts::LockableIsResourceManager::remove(EntityPtr entity)
{
    assert(entity != nullptr);

    auto component = getComponent<IsResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    resourceManager.remove(component->getResourceType(), entity);
}
