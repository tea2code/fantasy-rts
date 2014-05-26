#include <catch.hpp>

#include "LogStub.h"

#include <entity/ComponentIds.h>
#include <entity/impl/BlockedByImpl.h>
#include <entity/impl/BlockingImpl.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/SortOrderImpl.h>

#include <frts/log>
#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <memory>


TEST_CASE("Blocking.", "[entity]")
{
    frts::LogPtr log = std::make_shared<TestLog>();
    frts::SharedManagerPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

    frts::IdPtr block1 = frts::makeId("block1");
    frts::IdPtr block2 = frts::makeId("block2");

    frts::BlockedByPtr blockedBy1 = frts::makeBlockedBy(shared);
    blockedBy1->addBlock(block1);
    frts::BlockedByPtr blockedBy2 = frts::makeBlockedBy(shared);
    blockedBy2->addBlock(block2);
    frts::BlockingPtr blocking = frts::makeBlocking(shared);
    blocking->addBlock(block1);

    REQUIRE(blocking->blocks(blockedBy1));
    REQUIRE_FALSE(blocking->blocks(blockedBy2));
}

TEST_CASE("Entity.", "[entity]")
{
    frts::LogPtr log = std::make_shared<TestLog>();
    frts::SharedManagerPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

    frts::SortOrderPtr component = frts::makeSortOrder(shared);
    frts::IdPtr id = component->getComponentType();
    frts::EntityPtr entity = frts::makeEntity();

    REQUIRE_FALSE(entity->hasComponent(id));
    entity->addComponent(component);
    REQUIRE(entity->hasComponent(id));

    frts::SortOrderPtr entityComponent = frts::getComponent<frts::SortOrder>(id, entity);
    REQUIRE(component == entityComponent);

    entity->removeComponent(id);
    REQUIRE(entity->getComponent(id) == nullptr);
}
