#ifndef FRTS_REGIONIMPL_H
#define FRTS_REGIONIMPL_H

#include <region/Point.h>
#include <region/Region.h>
#include <region/RegionGenerator.h>
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

        std::vector<PointPtr> findFreeNeighbors(PointPtr pos, BlockingPtr blockedBy);
        PointPtr findFreeRandomPos(std::vector<Point::value> zLevels, BlockingPtr blockedBy);
        BlockPtr getBlock(PointPtr pos);
        std::vector<PointPtr> getNeightbors(PointPtr pos);
        PointPtr getPos(EntityPtr entity);
        void removeEntity(EntityPtr entity);
        void setPos(EntityPtr entity, PointPtr pos);

    private:
        using PosBlockMap = std::unordered_map<frts::PointPtr, frts::WriteableBlockPtr,
            frts::PointHash, frts::PointEqual>;
        using EntityPosMap = std::unordered_map<frts::EntityPtr, frts::PointPtr,
            frts::EntityHash, frts::EntityEqual>;

    private:
        EntityPosMap entityPos;
        PosBlockMap posBlock;
        Point::value mapSizeX;
        Point::value mapSizeY;
        RegionGeneratorPtr regionGenerator;

    private:
        WriteableBlockPtr getWriteableBlock(PointPtr pos);
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
