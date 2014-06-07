#include <catch.hpp>

#include <entity/ComponentIds.h>
#include <entity/impl/BlockedByImpl.h>
#include <entity/impl/BlockingImpl.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/SortOrderImpl.h>
#include <region/RegionGenerator.h>
#include <region/impl/BlockImpl.h>
#include <region/impl/PointImpl.h>
#include <region/impl/RegionImpl.h>

#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <algorithm>
#include <iterator>


TEST_CASE("Block.", "[region]")
{
    frts::IdPtr block1 = frts::makeId("block1");
    frts::IdPtr block2 = frts::makeId("block2");

    frts::BlockedByPtr blockedBy1 = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy1->addBlock(block1);
    frts::BlockedByPtr blockedBy2 = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy2->addBlock(block2);
    frts::BlockingPtr blocking = frts::makeBlocking(frts::makeId(frts::ComponentIds::blocking()));
    blocking->addBlock(block1);

    frts::SortOrderPtr sortOrder = frts::makeSortOrder(frts::makeId(frts::ComponentIds::sortOrder()));
    frts::IdPtr sort = sortOrder->getComponentType();

    frts::EntityPtr entity1 = frts::makeEntity();
    entity1->addComponent(blockedBy1);
    entity1->addComponent(blocking);
    entity1->addComponent(sortOrder);
    frts::EntityPtr entity2 = frts::makeEntity();
    entity2->addComponent(blockedBy1);
    entity2->addComponent(blocking);
    entity2->addComponent(sortOrder);
    frts::EntityPtr entity3 = frts::makeEntity();
    entity3->addComponent(blockedBy1);
    entity3->addComponent(blocking);
    entity3->addComponent(sortOrder);
    frts::EntityPtr entity4 = frts::makeEntity();
    entity4->addComponent(blockedBy1);
    entity4->addComponent(blocking);
    frts::EntityPtr entity5 = frts::makeEntity();
    entity5->addComponent(blockedBy1);
    entity5->addComponent(blocking);
    frts::EntityPtr entity6 = frts::makeEntity();
    entity6->addComponent(blockedBy1);
    entity6->addComponent(blocking);

    frts::BlockImplPtr blockImpl = frts::makeBlock(
                frts::makeId(frts::ComponentIds::blocking()),
                frts::makeId(frts::ComponentIds::sortOrder()));
    frts::BlockPtr block = blockImpl;

    blockImpl->insert(entity1);
    blockImpl->insert(entity2);
    blockImpl->insert(entity3);
    blockImpl->insert(entity4);

    auto sortEntities = block->getByComponent(sort);
    REQUIRE(sortEntities.size() == 3);
    auto it = sortEntities.begin();
    REQUIRE(*it == entity1);
    std::advance(it, 1);
    REQUIRE(*it == entity2);
    std::advance(it, 1);
    REQUIRE(*it == entity3);

    blockImpl->remove(entity3);

    sortEntities = block->getByComponent(sort);
    REQUIRE(sortEntities.size() == 2);
    it = sortEntities.begin();
    REQUIRE(*it == entity1);
    std::advance(it, 1);
    REQUIRE(*it == entity2);

    REQUIRE(block->has(entity4));
    REQUIRE_FALSE(block->has(entity5));
    REQUIRE_FALSE(block->has(entity6));

    REQUIRE(block->isBlocking(blockedBy1));
    REQUIRE_FALSE(block->isBlocking(blockedBy2));

    REQUIRE_NOTHROW(blockImpl->remove(entity3));
}


TEST_CASE("Point.", "[region]")
{
    SECTION("Length.")
    {
        Approx approx = Approx::custom().epsilon(0.0001);

        frts::PointPtr point = frts::makePoint(1, 1, 1);
        REQUIRE(point->getLength() == approx(1.732));

        point = frts::makePoint(45, 127, 10);
        REQUIRE(point->getLength() == approx(135.107));

        point = frts::makePoint(5, 3, 2);
        REQUIRE(point->getLength() == approx(6.164));

        point = frts::makePoint(-1, 1, 1);
        REQUIRE(point->getLength() == approx(1.732));

        point = frts::makePoint(45, -127, -10);
        REQUIRE(point->getLength() == approx(135.107));

        point = frts::makePoint(-5, -3, -2);
        REQUIRE(point->getLength() == approx(6.164));

        point = frts::makePoint(1, 2, 3);
        REQUIRE(point->getLength() == approx(3.742));
    }

    SECTION("Addition.")
    {
        frts::PointPtr point1 = frts::makePoint(1, 2, 1);
        frts::PointPtr point2 = frts::makePoint(3, 4, 1);
        frts::PointPtr point3 = point1 + point2;
        REQUIRE(point3->getX() == 4);
        REQUIRE(point3->getY() == 6);
        REQUIRE(point3->getZ() == 2);
    }

    SECTION("Substraction.")
    {
        frts::PointPtr point1 = frts::makePoint(1, 4, 3);
        frts::PointPtr point2 = frts::makePoint(3, 2, 2);
        frts::PointPtr point3 = point1 - point2;
        REQUIRE(point3->getX() == -2);
        REQUIRE(point3->getY() == 2);
        REQUIRE(point3->getZ() == 1);
    }

    SECTION("Cross product.")
    {
        frts::PointPtr point1 = frts::makePoint(2, 3, 4);
        frts::PointPtr point2 = frts::makePoint(5, 6, 7);
        frts::PointPtr point3 = point1 * point2;
        REQUIRE(point3->getX() == -3);
        REQUIRE(point3->getY() == 6);
        REQUIRE(point3->getZ() == -3);
    }

    SECTION("Scalar product.")
    {
        frts::PointPtr point1 = frts::makePoint(1, 2, 3);

        frts::PointPtr point2 = point1 * 5;
        REQUIRE(point2->getX() == 5);
        REQUIRE(point2->getY() == 10);
        REQUIRE(point2->getZ() == 15);

        frts::PointPtr point3 = 4 * point1;
        REQUIRE(point3->getX() == 4);
        REQUIRE(point3->getY() == 8);
        REQUIRE(point3->getZ() == 12);
    }

    SECTION("Equality.")
    {
        frts::PointPtr point1 = frts::makePoint(1, 1, 1);
        frts::PointPtr point2 = frts::makePoint(1, 1, 1);
        frts::PointPtr point3 = frts::makePoint(1, 2, 1);
        REQUIRE(point1 == point2);
        REQUIRE(point1 != point3);
        REQUIRE(point2 != point3);
    }
}

namespace frts
{
    class TestRegionGenerator : public RegionGenerator
    {
    public:
        TestRegionGenerator()
            : blockingType{makeId(ComponentIds::blocking())},
              sortOrderType{makeId(ComponentIds::sortOrder())}
        {}

        std::map<PointPtr, WriteableBlockPtr> allBlocks(Point::value zLevel) override
        {
            std::map<PointPtr, WriteableBlockPtr> result;
            result[makePoint(0, 0, zLevel)] = makeBlock(blockingType, sortOrderType);
            result[makePoint(0, 1, zLevel)] = makeBlock(blockingType, sortOrderType);
            result[makePoint(1, 0, zLevel)] = makeBlock(blockingType, sortOrderType);
            result[makePoint(1, 1, zLevel)] = makeBlock(blockingType, sortOrderType);
            return result;
        }

        WriteableBlockPtr newBlock(PointPtr) override
        {
            return makeBlock(blockingType, sortOrderType);
        }

    private:
        IdPtr blockingType;
        IdPtr sortOrderType;
    };
}

TEST_CASE("Region.", "[region]")
{
    frts::IdPtr block1 = frts::makeId("block1");
    frts::IdPtr block2 = frts::makeId("block2");

    frts::BlockedByPtr blockedBy1 = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy1->addBlock(block1);
    frts::BlockedByPtr blockedBy2 = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy2->addBlock(block2);
    frts::BlockingPtr blocking = frts::makeBlocking(frts::makeId(frts::ComponentIds::blocking()));
    blocking->addBlock(block1);

    frts::SortOrderPtr sortOrder = frts::makeSortOrder(frts::makeId(frts::ComponentIds::sortOrder()));
    frts::IdPtr sort = sortOrder->getComponentType();

    frts::EntityPtr entity1 = frts::makeEntity();
    entity1->addComponent(blockedBy1);
    entity1->addComponent(blocking);
    entity1->addComponent(sortOrder);
    frts::EntityPtr entity2 = frts::makeEntity();
    entity2->addComponent(blockedBy1);
    entity2->addComponent(blocking);

    frts::PointPtr point1 = frts::makePoint(0, 0, -1);
    frts::PointPtr point2 = frts::makePoint(0, 0, 0);
    frts::PointPtr point3 = frts::makePoint(0, 0, 1);

    frts::RegionGeneratorPtr regionGenerator = std::make_shared<frts::TestRegionGenerator>();
    frts::RegionPtr region = frts::makeRegion(2, 2, regionGenerator);

    region->setPos(entity1, point1);
    region->setPos(entity2, point3);

    SECTION("Find free random position.")
    {
        for (int i = 0; i < 100; ++i)
        {
            frts::PointPtr point = region->findFreeRandomPos({-1}, blockedBy1);
            REQUIRE(point != point1);
        }
    }

    SECTION("Find free neightbors.")
    {
        std::vector<frts::PointPtr> correctPositions = {
            frts::makePoint(0, 1, 0), frts::makePoint(1, 0, 0)
        };
        auto positions = region->findFreeNeighbors(point2, blockedBy1);
        REQUIRE(positions.size() == correctPositions.size());
        for(auto pos : positions)
        {
            REQUIRE(std::find(correctPositions.begin(), correctPositions.end(), pos) !=
                    correctPositions.end());
        }
    }

    SECTION("Get neightbors.")
    {
        std::vector<frts::PointPtr> correctPositions = {
            frts::makePoint(0, 1, 0), frts::makePoint(1, 0, 0), point1, point3
        };
        auto positions = region->getNeightbors(point2);
        REQUIRE(positions.size() == correctPositions.size());
        for(auto pos : positions)
        {
            REQUIRE(std::find(correctPositions.begin(), correctPositions.end(), pos) !=
                    correctPositions.end());
        }
    }

    SECTION("Get block.")
    {
        auto block = region->getBlock(point1);
        auto foundEntity = *block->getByComponent(sort).begin();
        REQUIRE(foundEntity == entity1);
    }

    SECTION("Get/set/remove entities.")
    {
        REQUIRE(region->getPos(entity1) == point1);
        REQUIRE(region->getPos(entity1) != point2);
        frts::PointPtr lastPos = region->setPos(entity1, point2);
        REQUIRE(lastPos == point1);
        REQUIRE(region->getPos(entity1) != point1);
        REQUIRE(region->getPos(entity1) == point2);
        lastPos = region->removeEntity(entity1);
        REQUIRE(lastPos == point2);
        REQUIRE(region->getPos(entity1) == nullptr);
    }
}
