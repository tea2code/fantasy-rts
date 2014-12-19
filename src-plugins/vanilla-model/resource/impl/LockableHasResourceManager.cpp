#include "LockableHasResourceManager.h"

#include <entity/HasResource.h>


frts::LockableHasResourceManager::LockableHasResourceManager(
        IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo)
    : componentType{componentType}, resourceManager{distAlgo, region}
{
}

void frts::LockableHasResourceManager::add(EntityPtr entity)
{
    assert(entity != nullptr);

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
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    return resourceManager.findNearest(entityGroup, resourceType, pos, shared_from_this(), shared);
}

frts::EntityPtr frts::LockableHasResourceManager::getEntity(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    return resourceManager.getEntity(lock);
}

frts::IdPtr frts::LockableHasResourceManager::getResourceType(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    return resourceManager.getResourceType(lock);
}

bool frts::LockableHasResourceManager::isValid(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    return resourceManager.isValid(lock);
}

void frts::LockableHasResourceManager::release(ResourceLockPtr lock)
{
    assert(lock != nullptr);

    resourceManager.release(lock);
}

void frts::LockableHasResourceManager::remove(EntityPtr entity)
{
    assert(entity != nullptr);

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
