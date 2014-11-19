#include <catch.hpp>

#include <main/ModelFactory.h>
#include <main/ModelIds.h>
#include <region/RegionGenerator.h>
#include <region/impl/BlockImpl.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>

#include <array>
#include <unordered_map>


namespace test
{
    class TestRegionGenerator : public frts::RegionGenerator
    {
    public:
        using Map = std::array<std::array<char, 10>, 10>;

    public:
        /**
         * @param blockingType The component type id of the blocking component.
         * @param sortOrderType The component type id of the sort order component.
         * @param mapSizeX The map size in x direction.
         * @param mapSizeY The map size in y direction.
         * @param maps Collection of maps for several z-levels.
         */
        TestRegionGenerator(frts::IdPtr blockingType, frts::IdPtr sortOrderType,
                            frts::Point::value mapSizeX, frts::Point::value mapSizeY,
                            std::unordered_map<int, Map> maps)
            : blockingType{blockingType}, sortOrderType{sortOrderType}, mapSizeX{mapSizeX},
              mapSizeY{mapSizeY}, maps{maps}
        {}

        std::map<frts::PointPtr, frts::WriteableBlockPtr> allBlocks(frts::Point::value zLevel, frts::SharedManagerPtr shared) override
        {
            auto modelFactory = frts::getUtility<frts::ModelFactory>(shared, frts::ModelIds::modelFactory());

            std::map<frts::PointPtr, frts::WriteableBlockPtr> result;
            for (frts::Point::value x = 0; x < mapSizeX; ++x)
            {
                for (frts::Point::value y = 0; y < mapSizeY; ++y)
                {
                    auto pos = modelFactory->makePoint(x, y, zLevel);
                    result[pos] = newBlock(pos, shared);
                }
            }
            return result;
        }

        frts::WriteableBlockPtr newBlock(frts::PointPtr pos, frts::SharedManagerPtr shared) override
        {
            auto modelFactory = frts::getUtility<frts::ModelFactory>(shared, frts::ModelIds::modelFactory());

            auto block = frts::makeBlock(blockingType, sortOrderType);
            block->insert(modelFactory->makeEntity(shared->makeId("entity.grass"), shared));
            return block;
        }

    private:
        frts::IdPtr blockingType;
        frts::IdPtr sortOrderType;
        frts:: Point::value mapSizeX;
        frts::Point::value mapSizeY;
        std::unordered_map<int, Map> maps;
    };
}


TEST_CASE("Pathfinder.", "[pathfinding]")
{

}
