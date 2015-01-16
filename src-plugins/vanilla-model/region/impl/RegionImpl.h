#ifndef FRTS_REGIONIMPL_H
#define FRTS_REGIONIMPL_H

#include <region/Point.h>
#include <region/Region.h>
#include <regiongenerator/RegionGenerator.h>
#include <region/WriteableBlock.h>

#include <unordered_map>

// Benchmarks shown a ~7% faster lookup. But that isn't significant enough to activate this
// obvious more complicated code.
//#define FAST_POS_BLOCK
#ifdef FAST_POS_BLOCK
#include <vector>
#endif

namespace frts
{
    class RegionImpl : public Region
    {
    public:
        /**
         * @param mapSizeX Size of map in x direction.
         * @param mapSizeY Size of map in y direction.
         * @param regionGenerator The region generator.
         */
        RegionImpl(Point::value mapSizeX, Point::value mapSizeY,
                   const RegionGeneratorPtr& regionGenerator);

        PointVector findFreeNeighbors(const PointPtr& pos, const BlockedByPtr& blockedBy, bool sameZLevel, const SharedManagerPtr& shared) override;
        PointPtr findFreeRandomPos(const std::vector<Point::value>& zLevels, const BlockedByPtr& blockedBy, const SharedManagerPtr& shared) override;
        BlockPtr getBlock(const PointPtr& pos, const SharedManagerPtr& shared) override;
        PointVector getNeightbors(const PointPtr& pos, bool sameZLevel, const SharedManagerPtr& shared) override;
        PointPtr getPos(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        PointPtr removeEntity(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        PointPtr setPos(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared) override;

    private:
        using PosBlockVector = std::vector<std::vector<std::vector<WriteableBlockPtr>>>;
        using PosBlockMap = std::unordered_map<PointPtr, WriteableBlockPtr>;
        using EntityPosMap = std::unordered_map<EntityPtr, PointPtr>;

    private:
        EntityPosMap entityPos;
        Point::value mapSizeX;
        Point::value mapSizeY;
        RegionGeneratorPtr regionGenerator;

        /**
         * @brief General lookup of blocks.
         */
        PosBlockMap posBlock;

        #ifdef FAST_POS_BLOCK
        /**
         * @brief Faster lookup of blocks using vectors and the coordinate values in order z, x and y. Works
         *        only on certain z-levels.
         */
        PosBlockVector fastPosBlock;

        Point::value fastLookupLow = -10;
        Point::value fastLookupHigh = 5;
        #endif

    private:
        WriteableBlockPtr getWriteableBlock(const PointPtr& pos, const SharedManagerPtr& shared);
    };

    /**
     * @brief Create new region object.
     * @param mapSizeX Size of map in x direction.
     * @param mapSizeY Size of map in y direction.
     * @param regionGenerator The region generator.
     * @return The region pointer.
     */
    inline RegionPtr makeRegion(Point::value mapSizeX, Point::value mapSizeY,
                                const RegionGeneratorPtr& regionGenerator)
    {
        assert(regionGenerator != nullptr);

        return std::make_shared<RegionImpl>(mapSizeX, mapSizeY, regionGenerator);
    }
}

#endif // FRTS_REGIONIMPL_H
