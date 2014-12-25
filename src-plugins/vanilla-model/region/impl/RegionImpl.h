#ifndef FRTS_REGIONIMPL_H
#define FRTS_REGIONIMPL_H

#include <region/Point.h>
#include <region/Region.h>
#include <regiongenerator/RegionGenerator.h>
#include <region/WriteableBlock.h>

#include <unordered_map>
//#include <vector>


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
                   RegionGeneratorPtr regionGenerator);

        PointVector findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy, bool sameZLevel, SharedManagerPtr shared) override;
        PointPtr findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy, SharedManagerPtr shared) override;
        BlockPtr getBlock(PointPtr pos, SharedManagerPtr shared) override;
        PointVector getNeightbors(PointPtr pos, bool sameZLevel, SharedManagerPtr shared) override;
        PointPtr getPos(EntityPtr entity, SharedManagerPtr shared) override;
        PointPtr removeEntity(EntityPtr entity, SharedManagerPtr shared) override;
        PointPtr setPos(EntityPtr entity, PointPtr pos, SharedManagerPtr shared) override;

    private:
        using PosBlockVector = std::vector<std::vector<std::vector<WriteableBlockPtr>>>;
        using PosBlockMap = std::unordered_map<PointPtr, WriteableBlockPtr, PointHash, PointEqual>;
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

//        /**
//         * @brief Faster lookup of blocks using vectors and the coordinate values in order z, x and y. Works
//         *        only on certain z-levels.
//         */
//        PosBlockVector fastPosBlock;

//        Point::value fastLookupLow = -10;
//        Point::value fastLookupHigh = 5;

    private:
        WriteableBlockPtr getWriteableBlock(PointPtr pos, SharedManagerPtr shared);
    };

    /**
     * @brief Create new region object.
     * @param mapSizeX Size of map in x direction.
     * @param mapSizeY Size of map in y direction.
     * @param regionGenerator The region generator.
     * @return The region pointer.
     */
    inline RegionPtr makeRegion(Point::value mapSizeX, Point::value mapSizeY,
                                RegionGeneratorPtr regionGenerator)
    {
        assert(regionGenerator != nullptr);

        return std::make_shared<RegionImpl>(mapSizeX, mapSizeY, regionGenerator);
    }
}

#endif // FRTS_REGIONIMPL_H
