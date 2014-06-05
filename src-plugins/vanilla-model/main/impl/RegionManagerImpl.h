#ifndef FRTS_REGIONMANAGERIMPL_H
#define FRTS_REGIONMANAGERIMPL_H

#include <main/RegionManager.h>


namespace frts
{
    class RegionManagerImpl : public RegionManager
    {
    public:
        RegionManagerImpl();

        void addChangedPos(PointPtr pos);
        std::vector<PointPtr> findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy);
        PointPtr findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy);
        ResourceLockPtr findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos);
        ResourceLockPtr findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos);
        BlockPtr getBlock(PointPtr pos);
        std::unordered_set<PointPtr> getChangedPos();
        std::string getName() const;
        std::vector<PointPtr> getNeightbors(PointPtr pos);
        PointPtr getPos(EntityPtr entity);
        void removeEntity(EntityPtr entity);
        void resetChangedPos();
        void setPos(EntityPtr entity, PointPtr pos);
    };

    /**
     * @brief Create new region manager.
     * @return The region manager.
     */
    inline RegionManagerPtr makeRegionManager()
    {
        return std::make_shared<RegionManagerImpl>();
    }
}

#endif // FRTS_REGIONMANAGERIMPL_H
