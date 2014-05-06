#include <catch.hpp>

#include <region/impl/PointImpl.h>

#include <memory>


TEST_CASE("Point.", "[region]")
{
    SECTION("Length.")
    {
        Approx approx = Approx::custom().epsilon(0.0001);

        frts::PointPtr point = std::make_shared<frts::PointImpl>(1, 1, 1);
        REQUIRE(point->getLength() == approx(1.732));

        point = std::make_shared<frts::PointImpl>(45, 127, 10);
        REQUIRE(point->getLength() == approx(135.107));

        point = std::make_shared<frts::PointImpl>(5, 3, 2);
        REQUIRE(point->getLength() == approx(6.164));

        point = std::make_shared<frts::PointImpl>(-1, 1, 1);
        REQUIRE(point->getLength() == approx(1.732));

        point = std::make_shared<frts::PointImpl>(45, -127, -10);
        REQUIRE(point->getLength() == approx(135.107));

        point = std::make_shared<frts::PointImpl>(-5, -3, -2);
        REQUIRE(point->getLength() == approx(6.164));

        point = std::make_shared<frts::PointImpl>(1, 2, 3);
        REQUIRE(point->getLength() == approx(3.742));
    }

    SECTION("Addition.")
    {
        frts::PointPtr point1 = std::make_shared<frts::PointImpl>(1, 2, 1);
        frts::PointPtr point2 = std::make_shared<frts::PointImpl>(3, 4, 1);
        frts::PointPtr point3 = *point1 + *point2;
        REQUIRE(point3->getX() == 4);
        REQUIRE(point3->getY() == 6);
        REQUIRE(point3->getZ() == 2);

    }

    SECTION("Substraction.")
    {
        frts::PointPtr point1 = std::make_shared<frts::PointImpl>(1, 4, 3);
        frts::PointPtr point2 = std::make_shared<frts::PointImpl>(3, 2, 2);
        frts::PointPtr point3 = *point1 - *point2;
        REQUIRE(point3->getX() == -2);
        REQUIRE(point3->getY() == 2);
        REQUIRE(point3->getZ() == 1);
    }

    SECTION("Cross product.")
    {
        frts::PointPtr point1 = std::make_shared<frts::PointImpl>(2, 3, 4);
        frts::PointPtr point2 = std::make_shared<frts::PointImpl>(5, 6, 7);
        frts::PointPtr point3 = *point1 * *point2;
        REQUIRE(point3->getX() == -3);
        REQUIRE(point3->getY() == 6);
        REQUIRE(point3->getZ() == -3);
    }

    SECTION("Scalar product.")
    {
        frts::PointPtr point1 = std::make_shared<frts::PointImpl>(1, 2, 3);

        frts::PointPtr point2 = *point1 * 5;
        REQUIRE(point2->getX() == 5);
        REQUIRE(point2->getY() == 10);
        REQUIRE(point2->getZ() == 15);

        frts::PointPtr point3 = 4 * *point1;
        REQUIRE(point3->getX() == 4);
        REQUIRE(point3->getY() == 8);
        REQUIRE(point3->getZ() == 12);
    }

    SECTION("Equality.")
    {
        frts::PointPtr point1 = std::make_shared<frts::PointImpl>(1, 1, 1);
        frts::PointPtr point2 = std::make_shared<frts::PointImpl>(1, 1, 1);
        frts::PointPtr point3 = std::make_shared<frts::PointImpl>(1, 2, 1);
        REQUIRE(*point1 == *point2);
        REQUIRE(*point1 != *point3);
        REQUIRE(*point2 != *point3);
    }


}
