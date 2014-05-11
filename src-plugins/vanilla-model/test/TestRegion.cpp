#include <catch.hpp>

#include <entity/impl/BlockingImpl.h>
#include <entity/impl/DynamicEntityImpl.h>
#include <entity/impl/ResourceImpl.h>
#include <region/impl/BlockImpl.h>
#include <region/impl/PointImpl.h>

#include <iterator>


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


TEST_CASE("Block.", "[region]")
{
    frts::BlockingPtr blockedBy1 = frts::makeBlocking(true, false);
    frts::BlockingPtr blockedBy2 = frts::makeBlocking(false, false);
    frts::BlockingPtr blocking = frts::makeBlocking(true, false);

    frts::DynamicEntityPtr entity1 = frts::makeDynamicEntity(blockedBy1, blocking, nullptr, 3);
    frts::DynamicEntityPtr entity2 = frts::makeDynamicEntity(blockedBy1, blocking, nullptr, 1);
    frts::DynamicEntityPtr entity3 = frts::makeDynamicEntity(blockedBy1, blocking, nullptr, 2);
    frts::ResourcePtr entity4 = frts::makeResource(blockedBy1, blocking, nullptr, 0);
    frts::ResourcePtr entity5 = frts::makeResource(blockedBy1, blocking, nullptr, 0);
    frts::ResourcePtr entity6 = frts::makeResource(blockedBy1, blocking, nullptr, 1);

    frts::BlockImplPtr blockImpl = frts::makeBlock();
    frts::BlockPtr block = blockImpl;

    blockImpl->insert(entity1);
    blockImpl->insert(entity2);
    blockImpl->insert(entity3);
    blockImpl->insert(entity4);

    auto dynamicEntities = block->getByType(frts::Entity::Type::Dynamic);
    REQUIRE(dynamicEntities.size() == 3);
    auto it = dynamicEntities.begin();
    REQUIRE(*it == entity2);
    std::advance(it, 1);
    REQUIRE(*it == entity3);
    std::advance(it, 1);
    REQUIRE(*it == entity1);

    blockImpl->remove(entity3);

    dynamicEntities = block->getByType(frts::Entity::Type::Dynamic);
    REQUIRE(dynamicEntities.size() == 2);
    it = dynamicEntities.begin();
    REQUIRE(*it == entity2);
    std::advance(it, 1);
    REQUIRE(*it == entity1);

    REQUIRE(block->has(entity4));
    REQUIRE_FALSE(block->has(entity5));
    REQUIRE_FALSE(block->has(entity6));

    REQUIRE(block->isBlocking(blockedBy1));
    REQUIRE_FALSE(block->isBlocking(blockedBy2));
}
