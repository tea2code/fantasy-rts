#include "BaseLockableResourceManager.h"


frts::BaseLockableResourceManager::BaseLockableResourceManager()
{    
}

void frts::BaseLockableResourceManager::add(IdPtr resourceType, EntityPtr entity)
{
    freeResources[resourceType].insert(entity);
}

frts::ResourceLockPtr frts::BaseLockableResourceManager::findNearest(IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    ResourceLockPtr result = nullptr;

    /*
    auto resourceIt = freeResources.find(resourceType);
    if (resourceIt != freeResources.end())
    {
        for (auto entity : resourceIt->second)
        {
            auto entityIt = entityLocks.find(entity);
            if (entityIt != entityLocks.end() && entityIt->second->)
        }
    }
    */

    return result;
}

frts::EntityPtr frts::BaseLockableResourceManager::getEntity(ResourceLockPtr lock) const
{
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
    return lockInfo.find(lock) != lockInfo.end();
}

void frts::BaseLockableResourceManager::release(ResourceLockPtr lock)
{
    if (!isValid(lock))
    {
        return;
    }

    entityLocks[lockInfo[lock].entity].erase(lock);
    lockInfo.erase(lock);
}

void frts::BaseLockableResourceManager::remove(IdPtr resourceType, EntityPtr entity)
{
    freeResources[resourceType].erase(entity);
    auto it = entityLocks.find(entity);
    if (it != entityLocks.end())
    {
        for (auto lock : it->second)
        {
            lockInfo.erase(lock);
        }
        entityLocks.erase(entity);
    }
}

