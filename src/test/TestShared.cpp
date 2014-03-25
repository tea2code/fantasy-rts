#include <catch.hpp>

#include <shared/FrameImpl.h>
#include <shared/Id.h>

#include <string>


TEST_CASE("Create and use frame data.", "[shared]")
{
    double deltaTime = 0.002145;
    unsigned long long number = 4098353456392489llu;
    double runTime = 254121.54123;
    frts::FramePtr frame = frts::FramePtr(new frts::FrameImpl(deltaTime, number, runTime));

    REQUIRE(frame->getDeltaTime() == Approx(deltaTime));
    REQUIRE(frame->getNumber() == number);
    REQUIRE(frame->getRunTime() == Approx(runTime));
}


TEST_CASE("Create and use id.", "[shared]")
{
    std::string str1 = "test";
    frts::Id id1 = frts::Id::from(str1);
    frts::Id id2 = frts::Id::from(str1);

    std::string str2 = "testtest";
    frts::Id id3 = frts::Id::from(str2);

    REQUIRE(id1.toString() == str1);
    REQUIRE(id2.toString() == str1);
    REQUIRE(id3.toString() == str2);
    REQUIRE(id1 == id2);
    REQUIRE(id1 != id3);
    REQUIRE(id2 != id3);
}
