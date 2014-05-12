#ifndef FRTS_REGIONGENERATOR_H
#define FRTS_REGIONGENERATOR_H

#include "Block.h"
#include "Point.h"

#include <map>
#include <memory>


namespace frts
{
    class RegionGenerator;

    /**
     * @brief Pointer to RegionGenerator.
     */
    using RegionGeneratorPtr = std::shared_ptr<RegionGenerator>;

    /**
     * @brief A region generator creates all the blocks in a certain
     *        region.
     */
    class RegionGenerator
    {
    public:
        virtual ~RegionGenerator() {}

        /**
         * @brief Get all blocks of a certain z-level.
         * @param zLevel The z-level.
         * @return Mapping of points to block.
         */
        virtual std::map<PointPtr, BlockPtr> allBlocks(Point::value zLevel) = 0;

        /**
         * @brief Get a new point for given position.
         * @param pos The position.
         * @return The generated block.
         */
        virtual BlockPtr newBlock(PointPtr pos) = 0;
    };
}

#endif // FRTS_REGIONGENERATOR_H
