#ifndef FRTS_DEMOREGIONGENERATOR_H
#define FRTS_DEMOREGIONGENERATOR_H

#include <frts/vanillamodeldev>


namespace frts
{
    /**
     * @brief Demo/Test implementation of an region generator.
     */
    class DemoRegionGenerator : public RegionGenerator
    {
    public:
        /**
         * @param blockingType The component type id of the blocking component.
         * @param sortOrderType The component type id of the sort order component.
         * @param mapSizeX The map size in x direction.
         * @param mapSizeY The map size in y direction.
         */
        DemoRegionGenerator(IdPtr blockingType, IdPtr sortOrderType,
                            Point::value mapSizeX, Point::value mapSizeY);

        std::map<PointPtr, WriteableBlockPtr> allBlocks(Point::value zLevel, SharedManagerPtr shared) override;
        WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared) override;

    private:
        IdPtr blockingType;
        Point::value mapSizeX;
        Point::value mapSizeY;
        IdPtr sortOrderType;
    };

    /**
     * @brief Create new DemoRegionGenerator.
     * @param blockingType The component type id of the blocking component.
     * @param sortOrderType The component type id of the sort order component.
     * @param mapSizeX The map size in x direction.
     * @param mapSizeY The map size in y direction.
     * @return The region generator.
     */
    inline RegionGeneratorPtr makeDemoRegionGenerator(IdPtr blockingType, IdPtr sortOrderType,
                                                      Point::value mapSizeX, Point::value mapSizeY)
    {
        return std::make_shared<DemoRegionGenerator>(blockingType, sortOrderType, mapSizeX, mapSizeY);
    }
}

#endif // FRTS_DEMOREGIONGENERATOR_H
