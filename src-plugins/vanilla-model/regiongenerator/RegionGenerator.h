#ifndef FRTS_REGIONGENERATOR_H
#define FRTS_REGIONGENERATOR_H

#include <region/Point.h>
#include <region/WriteableBlock.h>

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
         * @brief Get a new point for given position.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The generated block.
         */
        virtual WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_REGIONGENERATOR_H