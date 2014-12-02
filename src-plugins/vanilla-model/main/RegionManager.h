#ifndef FRTS_REGIONMANAGER_H
#define FRTS_REGIONMANAGER_H

#include <entity/BlockedBy.h>
#include <region/Block.h>
#include <region/Point.h>
#include <resource/ResourceLock.h>

#include <frts/shared>

#include <memory>
#include <unordered_set>
#include <vector>


namespace frts
{
    class RegionManager;

    /**
     * @brief Pointer to RegionManager.
     */
    using RegionManagerPtr = std::shared_ptr<RegionManager>;

    /**
     * @brief The region manager is the access interface to all region and
     *        resource managing related methods. It represents a data value containing
     *        the region. It also manages a list of changed positions since last
     *        reset. The will mostly be set automatically but can be also set by
     *        hand.
     */
    class RegionManager : public DataValue
    {
    public:
        using PointSet = std::unordered_set<PointPtr, PointHash, PointEqual>;

    public:
        virtual ~RegionManager() {}

        /**
         * @brief Add changed positions. This function will check for nullpointer.
         * @param pos The position.
         */
        virtual void addChangedPos(PointPtr pos) = 0;

        /**
         * @brief Find free neightbors of given position.
         * @param pos The position.
         * @param blockedBy Description of what can block.
         * @param sameZLevel If true neightbors are only searched on the same z-level.
         * @param shared The shared manager.
         * @return List of free neightbors.
         */
        virtual std::vector<PointPtr> findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy, bool sameZLevel, SharedManagerPtr shared) = 0;

        /**
         * @brief Find random position.
         * @param zLevels List of z-levels on which should be searched.
         * @param blockedBy Description of what can block.
         * @param shared The shared manager.
         * @return A single position.
         */
        virtual PointPtr findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy, SharedManagerPtr shared) = 0;

        /**
         * @brief Find nearest resource.
         * @param entityGroup The entity group for which this resource is locked.
         * @param resourceType The resource type.
         * @param pos The start position.
         * @param shared The shared manager.
         * @return Lock to nearest resource or null.
         */
        virtual ResourceLockPtr findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared) = 0;

        /**
         * @brief Find nearest entity which contains a resource.
         * @param entityGroup The entity group for which this resource is locked.
         * @param resourceType The resource type.
         * @param pos The start position.
         * @param shared The shared manager.
         * @return Lock to nearest resource or null.
         */
        virtual ResourceLockPtr findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared) = 0;

        /**
         * @brief Get block at position.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The block.
         */
        virtual BlockPtr getBlock(PointPtr pos, SharedManagerPtr shared) = 0;

        /**
         * @brief Get list of all changed positions.
         * @return The changed positions.
         */
        virtual PointSet getChangedPos() = 0;

        /**
         * @brief Get all neightbors (north, east, south, west, up, down) of position.
         * @param pos The position.
         * @param sameZLevel If true neightbors are only searched on the same z-level.
         * @param shared The shared manager.
         * @return List of neightbors.
         */
        virtual std::vector<PointPtr> getNeightbors(PointPtr pos, bool sameZLevel, SharedManagerPtr shared) = 0;

        /**
         * @brief Get position of entity.
         * @param entity The entity.
         * @param shared The shared manager.
         * @return The position or null if entity is not in region.
         */
        virtual PointPtr getPos(EntityPtr entity, SharedManagerPtr shared) = 0;

        /**
         * @brief Remove entity from region. Will update changed positions.
         * @param entity The entity.
         * @param shared The shared manager.
         * @return The last position of the entity or null if entity was not in region.
         */
        virtual PointPtr removeEntity(EntityPtr entity, SharedManagerPtr shared) = 0;

        /**
         * @brief Reset changed positions.
         */
        virtual void resetChangedPos() = 0;

        /**
         * @brief Add entity at position. This will also move it if it already is
         *        in the region. Will update changed positions. Will update resources.
         * @param entity The entity.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The previous position of the entity or null if entity was not in region.
         */
        virtual PointPtr setPos(EntityPtr entity, PointPtr pos, SharedManagerPtr shared) = 0;

        /**
         * @brief If resource components of a entity change it is necessary to
         *        update the resource managers. This will automaticallay happen
         *        if you call setPos() on the entity.
         * @param entity The entity.
         * @param shared The shared manager.
         */
        virtual void updateResources(EntityPtr entity, SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_REGIONMANAGER_H
