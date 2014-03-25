#include <catch.hpp>

#include <shared/FrameImpl.h>

TEST_CASE("Create frame data.", "[shared]")
{
    double deltaTime = 0.002145;
    unsigned long long number = 4098353456392489llu;
    double runTime = 254121.54123;
    frts::FramePtr frame = frts::FramePtr(new frts::FrameImpl(deltaTime, number, runTime));

    REQUIRE(frame->getDeltaTime() == Approx(deltaTime));
    REQUIRE(frame->getNumber() == number);
    REQUIRE(frame->getRunTime() == Approx(runTime));
}
