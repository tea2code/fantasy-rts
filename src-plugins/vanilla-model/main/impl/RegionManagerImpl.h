#ifndef FRTS_REGIONMANAGERIMPL_H
#define FRTS_REGIONMANAGERIMPL_H

#include <main/RegionManager.h>
#include <region/Point.h>
#include <region/Region.h>
#include <resource/LockableResourceManager.h>


namespace frts
{
    class RegionManagerImpl : public RegionManager
    {
    public:
        RegionManagerImpl(RegionPtr region, LockableResourceManagerPtr resourceManager,
                          LockableResourceManagerPtr resourceEntityManager,
                          IdPtr hasResourceType, IdPtr isResourceType);

        void addChangedPos(PointPtr pos) override;
        std::vector<PointPtr> findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy) override;
        PointPtr findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy) override;
        ResourceLockPtr findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos) override;
        ResourceLockPtr findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos) override;
        BlockPtr getBlock(PointPtr pos) override;
        PointSet getChangedPos() override;
        std::string getName() const override;
        std::vector<PointPtr> getNeightbors(PointPtr pos) override;
        PointPtr getPos(EntityPtr entity) override;
        void removeEntity(EntityPtr entity) override;
        void resetChangedPos() override;
        void setPos(EntityPtr entity, PointPtr pos) override;
        void updateResources(EntityPtr entity) override;

    private:
        PointSet changedPos;
        IdPtr hasResourceType;
        IdPtr isResourceType;
        RegionPtr region;
        LockableResourceManagerPtr resourceManager;
        LockableResourceManagerPtr resourceEntityManager;
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
        return std::make_shared<RegionManagerImpl>(region, resourceManager, resourceEntityManager,
                                                   hasResourceType, isResourceType);
    }
}

#endif // FRTS_REGIONMANAGERIMPL_H
