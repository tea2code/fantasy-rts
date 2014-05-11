#include <catch.hpp>

#include <entity/impl/BaseEntityImpl.h>
#include <entity/impl/BlockingImpl.h>
#include <entity/impl/DynamicEntityImpl.h>
#include <entity/impl/ResourceImpl.h>
#include <entity/impl/StaticEntityImpl.h>
#include <entity/impl/TileImpl.h>

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

    frts::BaseEntityImpl entity(blockedBy, blocking, state, sortOrder);

    REQUIRE(entity.getBlockedBy()->wall() == blockedBy->wall());
    REQUIRE(entity.getBlockedBy()->water() == blockedBy->water());
    REQUIRE(entity.getBlocking()->wall() == blocking->wall());
    REQUIRE(entity.getBlocking()->water() == blocking->water());
    REQUIRE(entity.getStateId() == state);
    REQUIRE(entity.getSortOrder() == sortOrder);
}


TEST_CASE("DynamicEntity.", "[entity]")
{
    frts::BlockingPtr blockedBy = frts::makeBlocking(true, false);
    frts::BlockingPtr blocking = frts::makeBlocking(false, true);
    frts::IdPtr state = nullptr;
    int sortOrder = 3;

    frts::DynamicEntityPtr entity = frts::makeDynamicEntity(blockedBy, blocking, state, sortOrder);

    REQUIRE(entity->getBlockedBy()->wall() == blockedBy->wall());
    REQUIRE(entity->getBlockedBy()->water() == blockedBy->water());
    REQUIRE(entity->getBlocking()->wall() == blocking->wall());
    REQUIRE(entity->getBlocking()->water() == blocking->water());
    REQUIRE(entity->getStateId() == state);
    REQUIRE(entity->getSortOrder() == sortOrder);
    REQUIRE(entity->getType() == frts::Entity::Type::Dynamic);
}


TEST_CASE("Resource.", "[entity]")
{
    frts::BlockingPtr blockedBy = frts::makeBlocking(true, false);
    frts::BlockingPtr blocking = frts::makeBlocking(false, true);
    frts::IdPtr state = nullptr;
    int sortOrder = 3;

    frts::ResourcePtr entity = frts::makeResource(blockedBy, blocking, state, sortOrder);

    REQUIRE(entity->getBlockedBy()->wall() == blockedBy->wall());
    REQUIRE(entity->getBlockedBy()->water() == blockedBy->water());
    REQUIRE(entity->getBlocking()->wall() == blocking->wall());
    REQUIRE(entity->getBlocking()->water() == blocking->water());
    REQUIRE(entity->getStateId() == state);
    REQUIRE(entity->getSortOrder() == sortOrder);
    REQUIRE(entity->getType() == frts::Entity::Type::Resource);
}


TEST_CASE("StaticEntity.", "[entity]")
{
    frts::BlockingPtr blockedBy = frts::makeBlocking(true, false);
    frts::BlockingPtr blocking = frts::makeBlocking(false, true);
    frts::IdPtr state = nullptr;
    int sortOrder = 3;

    frts::StaticEntityPtr entity = frts::makeStaticEntity(blockedBy, blocking, state, sortOrder);

    REQUIRE(entity->getBlockedBy()->wall() == blockedBy->wall());
    REQUIRE(entity->getBlockedBy()->water() == blockedBy->water());
    REQUIRE(entity->getBlocking()->wall() == blocking->wall());
    REQUIRE(entity->getBlocking()->water() == blocking->water());
    REQUIRE(entity->getStateId() == state);
    REQUIRE(entity->getSortOrder() == sortOrder);
    REQUIRE(entity->getType() == frts::Entity::Type::Static);
}


TEST_CASE("Tile.", "[entity]")
{
    frts::BlockingPtr blockedBy = frts::makeBlocking(true, false);
    frts::BlockingPtr blocking = frts::makeBlocking(false, true);
    frts::IdPtr state = nullptr;
    int sortOrder = 3;

    frts::TilePtr entity = frts::makeTile(blockedBy, blocking, state, sortOrder);

    REQUIRE(entity->getBlockedBy()->wall() == blockedBy->wall());
    REQUIRE(entity->getBlockedBy()->water() == blockedBy->water());
    REQUIRE(entity->getBlocking()->wall() == blocking->wall());
    REQUIRE(entity->getBlocking()->water() == blocking->water());
    REQUIRE(entity->getStateId() == state);
    REQUIRE(entity->getSortOrder() == sortOrder);
    REQUIRE(entity->getType() == frts::Entity::Type::Tile);
}
