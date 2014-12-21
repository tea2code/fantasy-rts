#ifndef FRTS_REGIONMANAGERIMPL_H
#define FRTS_REGIONMANAGERIMPL_H

#include <main/RegionManager.h>
#include <region/Point.h>
#include <region/Region.h>
#include <resource/LockableResourceManager.h>

#include <frts/RecursiveLock.h>


namespace frts
{
    class RegionManagerImpl : public RegionManager
    {
    public:
        RegionManagerImpl(RegionPtr region, LockableResourceManagerPtr resourceManager,
                          LockableResourceManagerPtr resourceEntityManager,
                          IdPtr hasResourceType, IdPtr isResourceType);

        void addChangedPos(PointPtr pos) override;
        PointVector findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy, bool sameZLevel, SharedManagerPtr shared) override;
        PointPtr findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy, SharedManagerPtr shared) override;
        ResourceLockPtr findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared) override;
        ResourceLockPtr findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared) override;
        BlockPtr getBlock(PointPtr pos, SharedManagerPtr shared) override;
        PointUnorderedSet getChangedPos() override;
        std::string getName() const override;
        PointVector getNeightbors(PointPtr pos, bool sameZLevel, SharedManagerPtr shared) override;
        PointPtr getPos(EntityPtr entity, SharedManagerPtr shared) override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;
        PointPtr removeEntity(EntityPtr entity, SharedManagerPtr shared) override;
        void resetChangedPos() override;
        PointPtr setPos(EntityPtr entity, PointPtr pos, SharedManagerPtr shared) override;
        void updateResources(EntityPtr entity, SharedManagerPtr shared) override;

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
        void addChangedPosLockFree(PointPtr pos);

        /**
         * @brief Lock free implementation of updateResource().
         * @param entity The entity.
         * @param shared The shared manager.
         */
        void updateResourcesLockFree(EntityPtr entity, SharedManagerPtr shared);
    };

    /**
     * @brief Create new region manager.
     * @return The region manager.
     */
    inline RegionManagerPtr makeRegionManager(RegionPtr region,
                                              LockableResourceManagerPtr resourceManager,
                                              LockableResourceManagerPtr resourceEntityManager,
                                              IdPtr hasResourceType, IdPtr isResourceType)
    {
        assert(region != nullptr);

        return std::make_shared<RegionManagerImpl>(region, resourceManager, resourceEntityManager,
                                                   hasResourceType, isResourceType);
    }
}

#endif // FRTS_REGIONMANAGERIMPL_H
