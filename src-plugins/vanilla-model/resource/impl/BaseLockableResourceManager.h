#ifndef FRTS_BASELOCKABLERESOURCEMANAGER_H
#define FRTS_BASELOCKABLERESOURCEMANAGER_H

#include <entity/Entity.h>
#include <region/Point.h>
#include <region/Region.h>
#include <resource/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>
#include <resource/ResourceLock.h>

#include <frts/shared>

#include <unordered_map>
#include <unordered_set>


namespace frts
{
    class BaseLockableResourceManager
    {
    public:
        BaseLockableResourceManager(DistanceAlgorithmPtr distAlgo, RegionPtr region);

        void add(IdPtr resourceType, EntityPtr entity);
        ResourceLockPtr findNearest(IdPtr entityGroup, IdPtr resourceType,
                                    PointPtr pos, LockableResourceManagerPtr parent);
        EntityPtr getEntity(ResourceLockPtr lock) const;
        IdPtr getResourceType(ResourceLockPtr lock) const;
        bool isValid(ResourceLockPtr lock) const;
        void release(ResourceLockPtr lock);
        void remove(IdPtr resourceType, EntityPtr entity);

    private:
        struct LockInfo
        {
            EntityPtr entity;
            IdPtr entityGroup;
            IdPtr resourceType;
        };

        using EntitySet = std::unordered_set<EntityPtr>;
        using IdEntitiesMap = std::unordered_map<IdPtr, EntitySet, IdHash, IdEqual>;
        using LockInfoMap = std::unordered_map<ResourceLockPtr, LockInfo>;
        using EntityLocksMap = std::unordered_map<EntityPtr, std::unordered_set<ResourceLockPtr>>;

    private:
        DistanceAlgorithmPtr distAlgo;
        EntityLocksMap entityLocks;
        IdEntitiesMap resources;
        IdEntitiesMap lockedEntities;
        LockInfoMap lockInfo;
        RegionPtr region;
    };
}

#endif // FRTS_BASELOCKABLERESOURCEMANAGER_H
