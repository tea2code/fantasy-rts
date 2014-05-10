#include <catch.hpp>

#include <entity/impl/BaseEntityImpl.h>
#include <entity/impl/BlockingImpl.h>

#include <frts/shared>

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


TEST_CASE("BaseEntityImpl.", "[entity]")
{
    frts::BlockingPtr blockedBy = frts::makeBlocking(true, false);
    frts::BlockingPtr blocking = frts::makeBlocking(false, true);
    frts::IdPtr state = nullptr;
    int sortOrder = 3;

    frts::BaseEntityImplPtr entity = frts::makeBaseEntity(blockedBy, blocking, state, sortOrder);

    REQUIRE(entity->getBlockedBy()->wall() == blockedBy->wall());
    REQUIRE(entity->getBlockedBy()->water() == blockedBy->water());
    REQUIRE(entity->getBlocking()->wall() == blocking->wall());
    REQUIRE(entity->getBlocking()->water() == blocking->water());
    REQUIRE(entity->getStateId() == state);
    REQUIRE(entity->getSortOrder() == sortOrder);
}


TEST_CASE("DynamicEntity.", "[entity]")
{

}

