#include <catch.hpp>

#include <shared/FrameImpl.h>
#include <shared/IdImpl.h>

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
    frts::IdPtr id1 = frts::IdPtr(new frts::IdImpl(str1));
    frts::IdPtr id2 = frts::IdPtr(new frts::IdImpl(str1));

    std::string str2 = "testtest";
    frts::IdPtr id3 = frts::IdPtr(new frts::IdImpl(str2));

    REQUIRE(id1->toString() == str1);
    REQUIRE(id2->toString() == str1);
    REQUIRE(id3->toString() == str2);
    REQUIRE(*id1 == *id2);
    REQUIRE(*id1 != *id3);
    REQUIRE(*id2 != *id3);
}
