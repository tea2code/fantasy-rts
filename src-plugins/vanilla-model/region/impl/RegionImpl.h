#ifndef FRTS_REGIONIMPL_H
#define FRTS_REGIONIMPL_H

#include <region/Region.h>
#include <region/RegionGenerator.h>


namespace frts
{
    class RegionImpl : public Region
    {
    public:
        RegionImpl(RegionGeneratorPtr regionGenerator);

        std::vector<PointPtr> findFreeNeighbors(PointPtr pos, BlockingPtr blockedBy);
        PointPtr findFreeRandomPos(std::vector<Point::value> zLevels, BlockingPtr blockedBy);
        BlockPtr getBlock(PointPtr pos);
        std::vector<PointPtr> getNeightbors(PointPtr pos);
        PointPtr getPos(EntityPtr entity);
        void removeEntity(EntityPtr entity);
        void setPos(EntityPtr entity, PointPtr pos);

    private:
        RegionGeneratorPtr regionGenerator;
    };

    /**
     * @brief Create new region object.
     * @param regionGenerator The region generator.
     * @return The region pointer.
     */
    inline RegionPtr makeRegion(RegionGeneratorPtr regionGenerator)
    {
        return std::make_shared<RegionImpl>(regionGenerator);
    }
}

#endif // FRTS_REGIONIMPL_H
