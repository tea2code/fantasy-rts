#ifndef BASELOCKABLERESOURCEMANAGER_H
#define BASELOCKABLERESOURCEMANAGER_H

#include <entity/Entity.h>
#include <region/Point.h>
#include <resource/ResourceLock.h>

#include <frts/shared>

#include <unordered_map>
#include <unordered_set>


namespace frts
{
    class BaseLockableResourceManager
    {
    public:
        BaseLockableResourceManager();

        void add(IdPtr resourceType, EntityPtr entity);
        ResourceLockPtr findNearest(IdPtr entityGroup, IdPtr resourceType, PointPtr pos);
        EntityPtr getEntity(ResourceLockPtr lock) const;
        IdPtr getResourceType(ResourceLockPtr lock) const;
        bool isValid(ResourceLockPtr lock) const;
        void release(ResourceLockPtr lock);
        void remove(IdPtr resourceType, EntityPtr entity);

    private:
        struct LockInfo
        {
            EntityPtr entity;
            IdPtr resourceType;
        };

        using EntitySet = std::unordered_set<EntityPtr>;
        using ResourceEntitiesMap = std::unordered_map<IdPtr, EntitySet, IdHash, IdEqual>;
        using LockInfoMap = std::unordered_map<ResourceLockPtr, LockInfo>;
        using EntityLocksMap = std::unordered_map<EntityPtr, std::unordered_set<ResourceLockPtr>>;

    private:
        EntityLocksMap entityLocks;
        ResourceEntitiesMap freeResources;
        LockInfoMap lockInfo;
    };
}

#endif // BASELOCKABLERESOURCEMANAGER_H
