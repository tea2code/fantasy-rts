#ifndef FRTS_REGIONIMPL_H
#define FRTS_REGIONIMPL_H

#include <region/Point.h>
#include <region/Region.h>
#include <regiongenerator/RegionGenerator.h>
#include <region/WriteableBlock.h>

#include <unordered_map>


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
        using PosBlockMap = std::unordered_map<PointPtr, WriteableBlockPtr,
            PointHash, PointEqual>;
        using EntityPosMap = std::unordered_map<EntityPtr, PointPtr>;

    private:
        EntityPosMap entityPos;
        PosBlockMap posBlock;
        Point::value mapSizeX;
        Point::value mapSizeY;
        RegionGeneratorPtr regionGenerator;

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
        return std::make_shared<RegionImpl>(mapSizeX, mapSizeY, regionGenerator);
    }
}

#endif // FRTS_REGIONIMPL_H
