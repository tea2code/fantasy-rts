#ifndef FRTS_REGIONGENERATORIMPL_H
#define FRTS_REGIONGENERATORIMPL_H

#include <region/RegionGenerator.h>

#include <memory>


namespace frts
{
    class RegionGeneratorImpl : public RegionGenerator
    {
    public:
        /**
         * @param blockingType The component type id of the blocking component.
         * @param sortOrderType The component type id of the sort order component.
         * @param mapSizeX The map size in x direction.
         * @param mapSizeY The map size in y direction.
         */
        RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType,
                            Point::value mapSizeX, Point::value mapSizeY);

        std::map<PointPtr, WriteableBlockPtr> allBlocks(Point::value zLevel);
        WriteableBlockPtr newBlock(PointPtr pos);

    private:
        IdPtr blockingType;
        Point::value mapSizeX;
        Point::value mapSizeY;
        IdPtr sortOrderType;
    };

    /**
     * @brief Create new region generator.
     * @param blockingType The component type id of the blocking component.
     * @param sortOrderType The component type id of the sort order component.
     * @param mapSizeX The map size in x direction.
     * @param mapSizeY The map size in y direction.
     * @return The region generator.
     */
    inline RegionGeneratorPtr makeRegionGenerator(IdPtr blockingType, IdPtr sortOrderType,
                                                  Point::value mapSizeX, Point::value mapSizeY)
    {
        return std::make_shared<RegionGeneratorImpl>(blockingType, sortOrderType, mapSizeX, mapSizeY);
    }
}

#endif // FRTS_REGIONGENERATORIMPL_H
