#include "BaseLockableResourceManager.h"

#include "ResourceLockImpl.h"


frts::BaseLockableResourceManager::BaseLockableResourceManager(DistanceAlgorithmPtr distAlgo, RegionPtr region)
    : distAlgo{distAlgo}, region{region}
{    
}

void frts::BaseLockableResourceManager::add(IdPtr resourceType, EntityPtr entity)
{
    assert(resourceType != nullptr);
    assert(entity != nullptr);

    // Using a set allows to dismiss any contains check.
    resources[resourceType].insert(entity);
}

frts::ResourceLockPtr frts::BaseLockableResourceManager::findNearest(IdPtr entityGroup, IdPtr resourceType,
                                                                     PointPtr pos, LockableResourceManagerPtr parent,
                                                                     SharedManagerPtr shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(parent != nullptr);
    assert(shared != nullptr);

    EntityPtr foundEntity = nullptr;
    Point::length distance = -1;

    auto resourceIt = resources.find(resourceType);
    if (resourceIt != resources.end())
    {
        for (auto& entity : resourceIt->second)
        {
            if (lockedEntities[entityGroup].find(entity) != lockedEntities[entityGroup].end())
            {
                continue;
            }

            auto currentDistance = distAlgo->distance(pos, region->getPos(entity, shared));
            if (distance == -1 || currentDistance < distance)
            {
                distance = currentDistance;
                foundEntity = entity;
            }
        }
    }

    ResourceLockPtr result = nullptr;
    if (foundEntity != nullptr)
    {
        result = makeResourceLock(parent);
        entityLocks[foundEntity].insert(result);
        lockedEntities[entityGroup].insert(foundEntity);
        lockInfo[result].entity = foundEntity;
        lockInfo[result].entityGroup = entityGroup;
        lockInfo[result].resourceType = resourceType;
    }
    return result;
}

frts::EntityPtr frts::BaseLockableResourceManager::getEntity(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    EntityPtr result;
    auto it = lockInfo.find(lock);
    if (it != lockInfo.end())
    {
        result = it->second.entity;
    }
    return result;
}

frts::IdPtr frts::BaseLockableResourceManager::getResourceType(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    IdPtr result;
    auto it = lockInfo.find(lock);
    if (it != lockInfo.end())
    {
        result = it->second.resourceType;
    }
    return result;
}

bool frts::BaseLockableResourceManager::isValid(ResourceLockPtr lock) const
{
    assert(lock != nullptr);

    return lockInfo.find(lock) != lockInfo.end();
}

void frts::BaseLockableResourceManager::release(ResourceLockPtr lock)
{
    assert(lock != nullptr);

    if (!isValid(lock))
    {
        return;
    }

    auto info = lockInfo[lock];
    entityLocks[info.entity].erase(lock);
    lockedEntities[info.entityGroup].erase(info.entity);
    lockInfo.erase(lock);
}

void frts::BaseLockableResourceManager::remove(IdPtr resourceType, EntityPtr entity)
{
    assert(resourceType != nullptr);
    assert(entity != nullptr);

    resources[resourceType].erase(entity);
    auto it = entityLocks.find(entity);
    if (it != entityLocks.end())
    {
        auto locks = it->second;
        for (auto& lock : locks)
        {
            lock->release();
        }
        entityLocks.erase(entity);
    }
}

