#include <catch.hpp>

#include <entity/impl/BlockingImpl.h>

#include <memory>


TEST_CASE("Blocking.", "[entity]")
{
    frts::BlockingPtr blocks = frts::makeBlocking(true, false);
    frts::BlockingPtr blocked1 = frts::makeBlocking(true, false);
    frts::BlockingPtr blocked2 = frts::makeBlocking(false, true);

    REQUIRE(blocks->wall());
    REQUIRE_FALSE(blocks->water());

    REQUIRE(blocks->blocks(blocked1));
    REQUIRE_FALSE(blocks->blocks(blocked2));
}


TEST_CASE("Entity.", "[entity]")
{

}
