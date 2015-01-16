#ifndef FRTS_REGIONMANAGERIMPL_H
#define FRTS_REGIONMANAGERIMPL_H

#include <main/RegionManager.h>
#include <region/Point.h>
#include <region/Region.h>
#include <resource/LockableResourceManager.h>
#include <frts/BaseDataValue.h>

#include <frts/RecursiveLock.h>


namespace frts
{
    class RegionManagerImpl : public BaseDataValue<RegionManager>
    {
    public:
        RegionManagerImpl(const RegionPtr& region, const LockableResourceManagerPtr& resourceManager,
                          const LockableResourceManagerPtr& resourceEntityManager,
                          const IdPtr& hasResourceType, const IdPtr& isResourceType);

        void addChangedPos(const PointPtr& pos) override;
        PointVector findFreeNeighbors(const PointPtr& pos, const BlockedByPtr& blockedBy, bool sameZLevel, const SharedManagerPtr& shared) override;
        PointPtr findFreeRandomPos(const std::vector<Point::value>& zLevels, const BlockedByPtr& blockedBy, const SharedManagerPtr& shared) override;
        ResourceLockPtr findNearestResource(const IdPtr& entityGroup, const IdPtr& resourceType, const PointPtr& pos, const SharedManagerPtr& shared) override;
        ResourceLockPtr findNearestResourceEntity(const IdPtr& entityGroup, const IdPtr& resourceType, const PointPtr& pos, const SharedManagerPtr& shared) override;
        BlockPtr getBlock(const PointPtr& pos, const SharedManagerPtr& shared) override;
        PointUnorderedSet getChangedPos() override;
        PointVector getNeightbors(const PointPtr& pos, bool sameZLevel, const SharedManagerPtr& shared) override;
        PointPtr getPos(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        PointPtr removeEntity(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        void resetChangedPos() override;
        PointPtr setPos(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared) override;
        void updateResources(const EntityPtr& entity, const SharedManagerPtr& shared) override;

    private:
        PointUnorderedSet changedPos;
        IdPtr hasResourceType;
        IdPtr isResourceType;
        RegionPtr region;
        LockableResourceManagerPtr resourceManager;
        LockableResourceManagerPtr resourceEntityManager;

        RecursiveLock locker;

    private:
        /**
         * @brief Lock free implementation of addChangedPos().
         * @param pos The position.
         */
        void addChangedPosLockFree(const PointPtr& pos);

        /**
         * @brief Lock free implementation of updateResource().
         * @param entity The entity.
         * @param shared The shared manager.
         */
        void updateResourcesLockFree(const EntityPtr& entity, const SharedManagerPtr& shared);
    };

    /**
     * @brief Create new region manager.
     * @return The region manager.
     */
    inline RegionManagerPtr makeRegionManager(const RegionPtr& region,
                                              const LockableResourceManagerPtr& resourceManager,
                                              const LockableResourceManagerPtr& resourceEntityManager,
                                              const IdPtr& hasResourceType, const IdPtr& isResourceType)
    {
        assert(region != nullptr);

        return std::make_shared<RegionManagerImpl>(region, resourceManager, resourceEntityManager,
                                                   hasResourceType, isResourceType);
    }
}

#endif // FRTS_REGIONMANAGERIMPL_H
