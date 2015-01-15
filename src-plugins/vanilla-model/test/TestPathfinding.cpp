#include <catch.hpp>

#include <entity/impl/BlockingImpl.h>
#include <entity/impl/BlockedByImpl.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/TeleportImpl.h>
#include <region/impl/PointImpl.h>
#include <regiongenerator/RegionGenerator.h>
#include <region/impl/BlockImpl.h>
#include <region/impl/RegionImpl.h>
#include <main/ModelIds.h>
#include <main/impl/RegionManagerImpl.h>
#include <resource/impl/LockableHasResourceManager.h>
#include <resource/impl/LockableIsResourceManager.h>
#include <pathfinding/impl/EuclideanDistance.h>
#include <pathfinding/impl/ManhattanDistance.h>
#include <pathfinding/impl/AStar.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>

#include <array>
#include <memory>
#include <unordered_map>


#define MAP_SIZE 10

namespace test
{
    class TestRegionGenerator : public frts::RegionGenerator
    {
    public:    
        using Map = std::array<std::array<std::string, MAP_SIZE>, MAP_SIZE>;

    public:
        /**
         * @param blockingType The component type id of the blocking component.
         * @param sortOrderType The component type id of the sort order component.
         * @param maps Collection of maps for several z-levels.
         */
        TestRegionGenerator(frts::IdPtr blockingType, frts::IdPtr sortOrderType,
                            std::unordered_map<int, Map> maps, frts::IdPtr teleportType)
            : blockingType{blockingType}, sortOrderType{sortOrderType}, teleportType{teleportType}, maps{maps}
        {}

        std::string getSupportedConfig() const override
        {
            return {};
        }

        void init(frts::SharedManagerPtr) override
        {}

        frts::WriteableBlockPtr newBlock(frts::PointPtr pos, frts::SharedManagerPtr shared) override
        {
            auto entity = frts::makeEntity();

            auto id = maps.at(pos->getZ())
                          .at(static_cast<unsigned int>(pos->getY()))
                          .at(static_cast<unsigned int>(pos->getX()));
            if (id == "w")
            {
                auto blocking = frts::makeBlocking(blockingType);
                blocking->addBlock(shared->makeId(id));
                entity->addComponent(blocking);
            }
            else if (id == "s")
            {
                auto teleport = frts::makeTeleport(teleportType);
                if (firstTeleportEntity != nullptr)
                {
                    teleport->setTarget(firstTeleportEntity);
                    auto otherTeleport = frts::getComponent<frts::Teleport>(teleportType, firstTeleportEntity);
                    otherTeleport->setTarget(entity);
                }
                else
                {
                    firstTeleportEntity = entity;
                }
                entity->addComponent(teleport);
            }

            auto block = frts::makeBlock(blockingType, sortOrderType);
            block->insert(entity);
            return block;
        }

        void parseConfig(frts::ConfigNodePtr, frts::SharedManagerPtr) override
        {}

        void validateData(frts::SharedManagerPtr) override
        {}

    private:
        frts::IdPtr blockingType;
        frts::IdPtr sortOrderType;
        frts::IdPtr teleportType;
        std::unordered_map<int, Map> maps;

        frts::EntityPtr firstTeleportEntity;
    };
}


TEST_CASE("Pathfinder.", "[pathfinding]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto blockingType = shared->makeId("component.blocking");
    auto blockedByType = shared->makeId("component.blockedBy");
    auto sortOrderType = shared->makeId("component.sortorder");
    auto hasResourceType = shared->makeId("component.hasresource");
    auto isResourceType = shared->makeId("component.isresource");
    auto teleportType = shared->makeId("component.teleport");

    auto blockedBy = frts::makeBlockedBy(blockedByType);
    blockedBy->addBlock(shared->makeId("w"));

    auto distAlgo = frts::makeEuclideanDistance();

    auto walls = test::TestRegionGenerator::Map {
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w",
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w"
    };

    SECTION("No obstacle from (0, 0) to (9, 0), (0, 9), (9, 9).")
    {
        auto map = test::TestRegionGenerator::Map {
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g"
        };
        auto maps = std::unordered_map<int, test::TestRegionGenerator::Map> {
            {-1, walls},
            {0, map},
            {1, walls}
        };

        auto rg = std::make_shared<test::TestRegionGenerator>(blockingType, sortOrderType, maps, teleportType);
        auto region = frts::makeRegion(MAP_SIZE, MAP_SIZE, rg);
        auto resourceManager = frts::makeLockableIsResourceManager(isResourceType, region, distAlgo);
        auto resourceEntityManager = frts::makeLockableHasResourceManager(hasResourceType, region, distAlgo);
        auto rm = frts::makeRegionManager(region, resourceManager, resourceEntityManager, hasResourceType, isResourceType);
        shared->setDataValue(shared->makeId(frts::ModelIds::regionManager()), rm);

        frts::PathFinderPtr pathFinder = frts::makeAStar(distAlgo, teleportType);
        REQUIRE(pathFinder != nullptr);

        auto start = frts::makePoint(0, 0, 0);

        auto goal = frts::makePoint(9, 0, 0);
        auto path = pathFinder->findPath(start, goal, blockedBy, shared)->getCompletePath();
        REQUIRE(path.size() == 10);
        for (unsigned int i = 0; i < path.size(); ++i)
        {
            REQUIRE(path.at(i) == frts::makePoint(static_cast<frts::Point::value>(i), 0, 0));
        }

        goal = frts::makePoint(0, 9, 0);
        path = pathFinder->findPath(start, goal, blockedBy, shared)->getCompletePath();
        REQUIRE(path.size() == 10);
        for (unsigned int i = 0; i < path.size(); ++i)
        {
            REQUIRE(path.at(i) == frts::makePoint(0, static_cast<frts::Point::value>(i), 0));
        }

        goal = frts::makePoint(9, 9, 0);
        path = pathFinder->findPath(start, goal, blockedBy, shared)->getCompletePath();

        REQUIRE(path.size() == 19);

        // Based on floating point inaccuracy the result may differ. So lets just check start and goal.
        REQUIRE(path.at(0) == frts::makePoint(0, 0, 0));
        REQUIRE(path.at(18) == frts::makePoint(9, 9, 0));

        // It seems in release build accessing path.at(1) twice would result in a crush.
        auto point = path.at(1);
        bool secondPointOk = (point == frts::makePoint(1, 0, 0)) || (point == frts::makePoint(0, 1, 0));
        REQUIRE(secondPointOk);
    }

    SECTION("Snake path from (0, 0) to (9, 9).")
    {
        auto map = test::TestRegionGenerator::Map {
            "g", "w", "g", "g", "g", "w", "g", "g", "g", "w",
            "g", "w", "g", "w", "g", "w", "g", "w", "g", "w",
            "g", "w", "g", "w", "g", "w", "g", "w", "g", "w",
            "g", "w", "g", "w", "g", "w", "g", "w", "g", "w",
            "g", "w", "g", "w", "g", "w", "g", "w", "g", "w",
            "g", "w", "g", "w", "g", "w", "g", "w", "g", "w",
            "g", "w", "g", "w", "g", "w", "g", "w", "g", "w",
            "g", "w", "g", "w", "g", "w", "g", "w", "g", "w",
            "g", "w", "g", "w", "g", "w", "g", "w", "g", "w",
            "g", "g", "g", "w", "g", "g", "g", "w", "g", "g"
        };
        auto maps = std::unordered_map<int, test::TestRegionGenerator::Map> {
            {-1, walls},
            {0, map},
            {1, walls}
        };

        auto rg = std::make_shared<test::TestRegionGenerator>(blockingType, sortOrderType, maps, teleportType);
        auto region = frts::makeRegion(MAP_SIZE, MAP_SIZE, rg);
        auto resourceManager = frts::makeLockableIsResourceManager(isResourceType, region, distAlgo);
        auto resourceEntityManager = frts::makeLockableHasResourceManager(hasResourceType, region, distAlgo);
        auto rm = frts::makeRegionManager(region, resourceManager, resourceEntityManager, hasResourceType, isResourceType);
        shared->setDataValue(shared->makeId(frts::ModelIds::regionManager()), rm);

        frts::PathFinderPtr pathFinder = frts::makeAStar(distAlgo, teleportType);
        REQUIRE(pathFinder != nullptr);

        auto start = frts::makePoint(0, 0, 0);

        auto goal = frts::makePoint(9, 9, 0);
        auto path = pathFinder->findPath(start, goal, blockedBy, shared)->getCompletePath();

        REQUIRE(path.size() == 55);

        REQUIRE(path.at(0) == frts::makePoint(0, 0, 0));
        REQUIRE(path.at(1) == frts::makePoint(0, 1, 0));
        REQUIRE(path.at(2) == frts::makePoint(0, 2, 0));
        REQUIRE(path.at(3) == frts::makePoint(0, 3, 0));
        REQUIRE(path.at(4) == frts::makePoint(0, 4, 0));
        REQUIRE(path.at(5) == frts::makePoint(0, 5, 0));
        REQUIRE(path.at(6) == frts::makePoint(0, 6, 0));
        REQUIRE(path.at(7) == frts::makePoint(0, 7, 0));
        REQUIRE(path.at(8) == frts::makePoint(0, 8, 0));
        REQUIRE(path.at(9) == frts::makePoint(0, 9, 0));
        REQUIRE(path.at(10) == frts::makePoint(1, 9, 0));

        REQUIRE(path.at(11) == frts::makePoint(2, 9, 0));
        REQUIRE(path.at(12) == frts::makePoint(2, 8, 0));
        REQUIRE(path.at(13) == frts::makePoint(2, 7, 0));
        REQUIRE(path.at(14) == frts::makePoint(2, 6, 0));
        REQUIRE(path.at(15) == frts::makePoint(2, 5, 0));
        REQUIRE(path.at(16) == frts::makePoint(2, 4, 0));
        REQUIRE(path.at(17) == frts::makePoint(2, 3, 0));
        REQUIRE(path.at(18) == frts::makePoint(2, 2, 0));
        REQUIRE(path.at(19) == frts::makePoint(2, 1, 0));
        REQUIRE(path.at(20) == frts::makePoint(2, 0, 0));
        REQUIRE(path.at(21) == frts::makePoint(3, 0, 0));

        REQUIRE(path.at(22) == frts::makePoint(4, 0, 0));
        REQUIRE(path.at(23) == frts::makePoint(4, 1, 0));
        REQUIRE(path.at(24) == frts::makePoint(4, 2, 0));
        REQUIRE(path.at(25) == frts::makePoint(4, 3, 0));
        REQUIRE(path.at(26) == frts::makePoint(4, 4, 0));
        REQUIRE(path.at(27) == frts::makePoint(4, 5, 0));
        REQUIRE(path.at(28) == frts::makePoint(4, 6, 0));
        REQUIRE(path.at(29) == frts::makePoint(4, 7, 0));
        REQUIRE(path.at(30) == frts::makePoint(4, 8, 0));
        REQUIRE(path.at(31) == frts::makePoint(4, 9, 0));
        REQUIRE(path.at(32) == frts::makePoint(5, 9, 0));

        REQUIRE(path.at(33) == frts::makePoint(6, 9, 0));
        REQUIRE(path.at(34) == frts::makePoint(6, 8, 0));
        REQUIRE(path.at(35) == frts::makePoint(6, 7, 0));
        REQUIRE(path.at(36) == frts::makePoint(6, 6, 0));
        REQUIRE(path.at(37) == frts::makePoint(6, 5, 0));
        REQUIRE(path.at(38) == frts::makePoint(6, 4, 0));
        REQUIRE(path.at(39) == frts::makePoint(6, 3, 0));
        REQUIRE(path.at(40) == frts::makePoint(6, 2, 0));
        REQUIRE(path.at(41) == frts::makePoint(6, 1, 0));
        REQUIRE(path.at(42) == frts::makePoint(6, 0, 0));
        REQUIRE(path.at(43) == frts::makePoint(7, 0, 0));

        REQUIRE(path.at(44) == frts::makePoint(8, 0, 0));
        REQUIRE(path.at(45) == frts::makePoint(8, 1, 0));
        REQUIRE(path.at(46) == frts::makePoint(8, 2, 0));
        REQUIRE(path.at(47) == frts::makePoint(8, 3, 0));
        REQUIRE(path.at(48) == frts::makePoint(8, 4, 0));
        REQUIRE(path.at(49) == frts::makePoint(8, 5, 0));
        REQUIRE(path.at(50) == frts::makePoint(8, 6, 0));
        REQUIRE(path.at(51) == frts::makePoint(8, 7, 0));
        REQUIRE(path.at(52) == frts::makePoint(8, 8, 0));
        REQUIRE(path.at(53) == frts::makePoint(8, 9, 0));
        REQUIRE(path.at(54) == frts::makePoint(9, 9, 0));
    }

    SECTION("Changing z-level from (0, 0, 0) to (9, 0, 1).")
    {
        auto map1 = test::TestRegionGenerator::Map {
            "g", "g", "g", "g", "s", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w",
            "g", "g", "g", "g", "g", "w", "w", "w", "w", "w"
        };
        auto map2 = test::TestRegionGenerator::Map {
            "w", "w", "w", "w", "s", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g",
            "w", "w", "w", "w", "w", "g", "g", "g", "g", "g"
        };
        auto maps = std::unordered_map<int, test::TestRegionGenerator::Map> {
            {-1, walls},
            {0, map1},
            {1, map2},
            {2, walls}
        };

        auto rg = std::make_shared<test::TestRegionGenerator>(blockingType, sortOrderType, maps, teleportType);     
        auto region = frts::makeRegion(MAP_SIZE, MAP_SIZE, rg);
        auto resourceManager = frts::makeLockableIsResourceManager(isResourceType, region, distAlgo);
        auto resourceEntityManager = frts::makeLockableHasResourceManager(hasResourceType, region, distAlgo);
        auto rm = frts::makeRegionManager(region, resourceManager, resourceEntityManager, hasResourceType, isResourceType);
        shared->setDataValue(shared->makeId(frts::ModelIds::regionManager()), rm);

        // Before using teleport we must initialize them.
        for (frts::Point::value x = 0; x < MAP_SIZE; ++x)
        {
            for (frts::Point::value y = 0; y < MAP_SIZE; ++y)
            {
                auto pos = frts::makePoint(x, y, 0);
                rm->getBlock(pos, shared);
                pos = frts::makePoint(x, y, 1);
                rm->getBlock(pos, shared);
            }
        }

        frts::PathFinderPtr pathFinder = frts::makeAStar(distAlgo, teleportType);
        REQUIRE(pathFinder != nullptr);

        auto start = frts::makePoint(0, 0, 0);

        auto goal = frts::makePoint(9, 0, 1);
        auto path = pathFinder->findPath(start, goal, blockedBy, shared)->getCompletePath();
        REQUIRE(path.size() == 11);
        int z = 0;
        for (unsigned int i = 0; i < path.size(); ++i)
        {
            auto x = static_cast<frts::Point::value>(i);
            if (i >= 5)
            {
                z = 1;
                x -= 1;
            }
            REQUIRE(path.at(i) == frts::makePoint(x, 0, z));
        }
    }

    SECTION("Through wall from (0, 0, 0) to (9, 0, 0).")
    {
        auto map = test::TestRegionGenerator::Map {
            "g", "g", "g", "g", "s", "w", "s", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "w", "g", "g", "g", "g"
        };
        auto maps = std::unordered_map<int, test::TestRegionGenerator::Map> {
            {-1, walls},
            {0, map},
            {1, walls}
        };

        auto rg = std::make_shared<test::TestRegionGenerator>(blockingType, sortOrderType, maps, teleportType);
        auto region = frts::makeRegion(MAP_SIZE, MAP_SIZE, rg);
        auto resourceManager = frts::makeLockableIsResourceManager(isResourceType, region, distAlgo);
        auto resourceEntityManager = frts::makeLockableHasResourceManager(hasResourceType, region, distAlgo);
        auto rm = frts::makeRegionManager(region, resourceManager, resourceEntityManager, hasResourceType, isResourceType);
        shared->setDataValue(shared->makeId(frts::ModelIds::regionManager()), rm);

        // Before using teleport we must initialize them.
        for (frts::Point::value x = 0; x < MAP_SIZE; ++x)
        {
            for (frts::Point::value y = 0; y < MAP_SIZE; ++y)
            {
                auto pos = frts::makePoint(x, y, 0);
                rm->getBlock(pos, shared);
            }
        }

        frts::PathFinderPtr pathFinder = frts::makeAStar(distAlgo, teleportType);
        REQUIRE(pathFinder != nullptr);

        auto start = frts::makePoint(0, 0, 0);

        auto goal = frts::makePoint(9, 0, 0);
        auto path = pathFinder->findPath(start, goal, blockedBy, shared)->getCompletePath();
        REQUIRE(path.size() == 9);
        for (unsigned int i = 0; i < path.size(); ++i)
        {
            auto x = static_cast<frts::Point::value>(i);
            if (i > 4)
            {
                x += 1;
            }
            REQUIRE(path.at(i) == frts::makePoint(x, 0, 0));
        }
    }

    SECTION("Don't jump z-levels from (0, 0, 0) to (9, 0, 1).")
    {
        auto map = test::TestRegionGenerator::Map {
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g",
            "g", "g", "g", "g", "g", "g", "g", "g", "g", "g"
        };
        auto maps = std::unordered_map<int, test::TestRegionGenerator::Map> {
            {-1, walls},
            {0, map},
            {1, map},
            {2, walls}
        };

        auto rg = std::make_shared<test::TestRegionGenerator>(blockingType, sortOrderType, maps, teleportType);
        auto region = frts::makeRegion(MAP_SIZE, MAP_SIZE, rg);
        auto resourceManager = frts::makeLockableIsResourceManager(isResourceType, region, distAlgo);
        auto resourceEntityManager = frts::makeLockableHasResourceManager(hasResourceType, region, distAlgo);
        auto rm = frts::makeRegionManager(region, resourceManager, resourceEntityManager, hasResourceType, isResourceType);
        shared->setDataValue(shared->makeId(frts::ModelIds::regionManager()), rm);

        frts::PathFinderPtr pathFinder = frts::makeAStar(distAlgo, teleportType);
        REQUIRE(pathFinder != nullptr);

        auto start = frts::makePoint(0, 0, 0);

        auto goal = frts::makePoint(9, 0, 1);
        auto path = pathFinder->findPath(start, goal, blockedBy, shared);
        REQUIRE_FALSE(path->pathExists());
        REQUIRE(path->getCompletePath().size() == 0);
    }
}

TEST_CASE("Euclidean distance.", "[pathfinding]")
{
    auto ed = frts::makeEuclideanDistance();
    REQUIRE(ed->distance(frts::makePoint(0, 0, 0), frts::makePoint(1, 1, 0)) == Approx(1.4142));
    REQUIRE(ed->distance(frts::makePoint(2, -1, 0), frts::makePoint(-2, 2, 0)) == Approx(5));
    REQUIRE(ed->distance(frts::makePoint(0, 3, 4), frts::makePoint(7, 6, 3)) == Approx(7.6811));
}

TEST_CASE("Manhattan distance.", "[pathfinding]")
{
    auto md = frts::makeManhattanDistance();
    REQUIRE(md->distance(frts::makePoint(0, 0, 0), frts::makePoint(1, 1, 0)) == Approx(2));
    REQUIRE(md->distance(frts::makePoint(2, -1, 0), frts::makePoint(-2, 2, 0)) == Approx(7));
    REQUIRE(md->distance(frts::makePoint(0, 3, 4), frts::makePoint(7, 6, 3)) == Approx(11));

    md = frts::makeManhattanDistance(2.5);
    REQUIRE(md->distance(frts::makePoint(0, 0, 0), frts::makePoint(1, 1, 0)) == Approx(5));
    REQUIRE(md->distance(frts::makePoint(2, -1, 0), frts::makePoint(-2, 2, 0)) == Approx(17.5));
    REQUIRE(md->distance(frts::makePoint(0, 3, 4), frts::makePoint(7, 6, 3)) == Approx(27.5));
}
