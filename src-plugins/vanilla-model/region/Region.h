#ifndef FRTS_REGION_H
#define FRTS_REGION_H

#include "Block.h"
#include "Point.h"

#include <entity/BlockedBy.h>
#include <entity/Entity.h>

#include <memory>
#include <stdexcept>
#include <vector>


namespace frts
{
    class Region;

    /**
     * @brief Pointer to Region.
     */
    using RegionPtr = std::shared_ptr<Region>;

    /**
     * @brief Representation of a region in the game world. Consists of blocks.
     *        No range checks for the positions are made.
     */
    class Region
    {
    public:
        virtual ~Region() {}

        /**
         * @brief Find free neightbors of given position.
         * @param pos The position.
         * @param blockedBy Description of what can block.
         * @param sameZLevel If true neightbors are only searched on the same z-level.
         * @param shared The shared manager.
         * @return List of free neightbors.
         */
        virtual PointVector findFreeNeighbors(const PointPtr& pos, const BlockedByPtr& blockedBy, bool sameZLevel, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Find random position.
         * @param zLevels List of z-levels on which should be searched.
         * @param blockedBy Description of what can block.
         * @param shared The shared manager.
         * @return A single position or nullptr if no is found.
         */
        virtual PointPtr findFreeRandomPos(const std::vector<Point::value>& zLevels, const BlockedByPtr& blockedBy, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Get block at position.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The block.
         */
        virtual BlockPtr getBlock(const PointPtr& pos, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Get all neightbors (north, east, south, west, up, down) of position.
         * @param pos The position.
         * @param sameZLevel If true neightbors are only searched on the same z-level.
         * @param shared The shared manager.
         * @return List of neightbors.
         */
        virtual PointVector getNeightbors(const PointPtr& pos, bool sameZLevel, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Get position of entity.
         * @param entity The entity.
         * @param shared The shared manager.
         * @return The position or null if entity is not in region.
         */
        virtual PointPtr getPos(const EntityPtr& entity, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Remove entity from region.
         * @param entity The entity.
         * @param shared The shared manager.
         * @return The last position of the entity or null if entity was not in region.
         */
        virtual PointPtr removeEntity(const EntityPtr& entity, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Add entity at position. This will also move it if it already is
         *        in the region.
         * @param entity The entity.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The previous position of the entity or null if entity was not in region.
         */
        virtual PointPtr setPos(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_REGION_H
