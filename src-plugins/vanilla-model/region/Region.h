#ifndef FRTS_REGION_H
#define FRTS_REGION_H

#include "Block.h"
#include "Point.h"

#include <entity/Blocking.h>
#include <entity/Entity.h>

#include <memory>
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
         * @return List of free neightbors.
         */
        virtual std::vector<PointPtr> findFreeNeighbors(PointPtr pos, BlockingPtr blockedBy) = 0;

        /**
         * @brief Find random position.
         * @param zLevels List of z-levels on which should be searched.
         * @param blockedBy Description of what can block.
         * @return A single position.
         */
        virtual PointPtr findFreeRandomPos(std::vector<Point::value> zLevels, BlockingPtr blockedBy) = 0;

        /**
         * @brief Get block at position.
         * @param pos The position.
         * @return The block.
         */
        virtual BlockPtr getBlock(PointPtr pos) = 0;

        /**
         * @brief Get all neightbors (north, east, south, west, up, down) of position.
         * @param pos The position.
         * @return List of neightbors.
         */
        virtual std::vector<PointPtr> getNeightbors(PointPtr pos) = 0;

        /**
         * @brief Get position of entity.
         * @param entity The entity.
         * @return The position or null if entity is not in region.
         */
        virtual PointPtr getPos(EntityPtr entity) = 0;

        /**
         * @brief Remove entity from region.
         * @param entity The entity.
         */
        virtual void removeEntity(EntityPtr entity) = 0;

        /**
         * @brief Add entity at position. This will also move it if it already is
         *        in the region.
         * @param entity The entity.
         * @param pos The position.
         */
        virtual void setPos(EntityPtr entity, PointPtr pos) = 0;
    };
}

#endif // FRTS_REGION_H
