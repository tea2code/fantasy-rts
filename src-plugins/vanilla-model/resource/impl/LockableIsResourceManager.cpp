#include "LockableIsResourceManager.h"

#include <entity/IsResource.h>


frts::LockableIsResourceManager::LockableIsResourceManager(const IdPtr& componentType, const RegionPtr& region,
                                                           const DistanceAlgorithmPtr& distAlgo)
    : componentType{componentType}, resourceManager{distAlgo, region}
{
}

void frts::LockableIsResourceManager::add(const EntityPtr& entity)
{
    assert(entity != nullptr);

    auto component = getComponent<IsResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    resourceManager.add(component->getResourceType(), entity);
}

frts::ResourceLockPtr frts::LockableIsResourceManager::findNearest(const IdPtr& entityGroup, const IdPtr& resourceType,
                                                                   const PointPtr& pos,
                                                                   const SharedManagerPtr& shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    return resourceManager.findNearest(entityGroup, resourceType, pos, shared_from_this(), shared);
}

frts::EntityPtr frts::LockableIsResourceManager::getEntity(const ResourceLockPtr& lock) const
{
    assert(lock != nullptr);

    return resourceManager.getEntity(lock);
}

frts::IdPtr frts::LockableIsResourceManager::getResourceType(const ResourceLockPtr& lock) const
{
    assert(lock != nullptr);

    return resourceManager.getResourceType(lock);
}

bool frts::LockableIsResourceManager::isValid(const ResourceLockPtr& lock) const
{
    assert(lock != nullptr);

    return resourceManager.isValid(lock);
}

void frts::LockableIsResourceManager::release(const ResourceLockPtr& lock)
{
    assert(lock != nullptr);

    resourceManager.release(lock);
}

void frts::LockableIsResourceManager::remove(const EntityPtr& entity)
{
    assert(entity != nullptr);

    auto component = getComponent<IsResource>(componentType, entity);
    if (component == nullptr)
    {
        return;
    }

    resourceManager.remove(component->getResourceType(), entity);
}
