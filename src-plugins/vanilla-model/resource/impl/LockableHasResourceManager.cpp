#include "LockableHasResourceManager.h"

#include <entity/HasResource.h>


frts::LockableHasResourceManager::LockableHasResourceManager(const IdPtr& componentType, const RegionPtr& region,
                                                             const DistanceAlgorithmPtr& distAlgo)
    : componentType{componentType}, resourceManager{distAlgo, region}
{
}

void frts::LockableHasResourceManager::add(const EntityPtr& entity)
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

frts::ResourceLockPtr frts::LockableHasResourceManager::findNearest(const IdPtr& entityGroup, const IdPtr& resourceType,
                                                                    const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    return resourceManager.findNearest(entityGroup, resourceType, pos, shared_from_this(), shared);
}

frts::EntityPtr frts::LockableHasResourceManager::getEntity(const ResourceLockPtr& lock) const
{
    assert(lock != nullptr);

    return resourceManager.getEntity(lock);
}

frts::IdPtr frts::LockableHasResourceManager::getResourceType(const ResourceLockPtr& lock) const
{
    assert(lock != nullptr);

    return resourceManager.getResourceType(lock);
}

bool frts::LockableHasResourceManager::isValid(const ResourceLockPtr& lock) const
{
    assert(lock != nullptr);

    return resourceManager.isValid(lock);
}

void frts::LockableHasResourceManager::release(const ResourceLockPtr& lock)
{
    assert(lock != nullptr);

    resourceManager.release(lock);
}

void frts::LockableHasResourceManager::remove(const EntityPtr& entity)
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
