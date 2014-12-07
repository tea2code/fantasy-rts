#ifndef FRTS_REGIONGENERATORIMPL_H
#define FRTS_REGIONGENERATORIMPL_H

#include <regiongenerator/RegionGenerator.h>

#include <memory>


namespace frts
{
    class RegionGeneratorImpl : public RegionGenerator
    {
    public:
        /**
         * @param blockingType The component type id of the blocking component.
         * @param sortOrderType The component type id of the sort order component.
         */
        RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType);

        WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared);

    private:
        IdPtr blockingType;
        IdPtr sortOrderType;

        Point::value surfaceZLevel = 0; // TODO Remove
    };

    /**
     * @brief Create new region generator.
     * @param blockingType The component type id of the blocking component.
     * @param sortOrderType The component type id of the sort order component.
     * @param mapSizeX The map size in x direction.
     * @param mapSizeY The map size in y direction.
     * @return The region generator.
     */
    inline RegionGeneratorPtr makeRegionGenerator(IdPtr blockingType, IdPtr sortOrderType)
    {
        return std::make_shared<RegionGeneratorImpl>(blockingType, sortOrderType);
    }
}

#endif // FRTS_REGIONGENERATORIMPL_H
