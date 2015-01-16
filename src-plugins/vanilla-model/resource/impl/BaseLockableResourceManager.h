#ifndef FRTS_BASELOCKABLERESOURCEMANAGER_H
#define FRTS_BASELOCKABLERESOURCEMANAGER_H

#include <entity/Entity.h>
#include <region/Point.h>
#include <region/Region.h>
#include <pathfinding/DistanceAlgorithm.h>
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
        BaseLockableResourceManager(const DistanceAlgorithmPtr& distAlgo, const RegionPtr& region);

        void add(const IdPtr& resourceType, const EntityPtr& entity);
        ResourceLockPtr findNearest(const IdPtr& entityGroup, const IdPtr& resourceType, const PointPtr& pos,
                                   const  LockableResourceManagerPtr& parent, const SharedManagerPtr& shared);
        EntityPtr getEntity(const ResourceLockPtr& lock) const;
        IdPtr getResourceType(const ResourceLockPtr& lock) const;
        bool isValid(const ResourceLockPtr& lock) const;
        void release(const ResourceLockPtr& lock);
        void remove(const IdPtr& resourceType, const EntityPtr& entity);

    private:
        struct LockInfo
        {
            EntityPtr entity;
            IdPtr entityGroup;
            IdPtr resourceType;
        };

        using EntitySet = EntityUnorderedSet;
        using IdEntitiesMap = std::unordered_map<IdPtr, EntitySet>;
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
