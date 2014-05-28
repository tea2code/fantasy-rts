#include <catch.hpp>

#include <entity/ComponentIds.h>
#include <entity/impl/BlockedByImpl.h>
#include <entity/impl/BlockingImpl.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/SortOrderImpl.h>
#include <region/impl/BlockImpl.h>

#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <memory>


TEST_CASE("Blocking/BlockedBy.", "[entity]")
{
    frts::IdPtr block1 = frts::makeId("block1");
    frts::IdPtr block2 = frts::makeId("block2");

    frts::BlockedByPtr blockedBy1 = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy1->addBlock(block1);
    frts::BlockedByPtr blockedBy2 = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy2->addBlock(block2);
    frts::BlockingPtr blocking = frts::makeBlocking(frts::makeId(frts::ComponentIds::blocking()));
    blocking->addBlock(block1);

    REQUIRE(blocking->blocks(blockedBy1));
    REQUIRE_FALSE(blocking->blocks(blockedBy2));
}

TEST_CASE("Entity.", "[entity]")
{
    frts::SortOrderPtr component = frts::makeSortOrder(frts::makeId(frts::ComponentIds::sortOrder()));
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

TEST_CASE("SortOrder.", "[entity]")
{
    frts::IdPtr sort = frts::makeId(frts::ComponentIds::sortOrder());

    frts::SortOrderPtr sortOrder1 = frts::makeSortOrder(sort, frts::SortOrder::DEFAULT);
    frts::SortOrderPtr sortOrder2 = frts::makeSortOrder(sort, frts::SortOrder::TOP);
    frts::SortOrderPtr sortOrder3 = frts::makeSortOrder(sort, frts::SortOrder::BOTTOM);

    frts::EntityPtr entity1 = frts::makeEntity();
    entity1->addComponent(sortOrder1);
    frts::EntityPtr entity2 = frts::makeEntity();
    entity2->addComponent(sortOrder2);
    frts::EntityPtr entity3 = frts::makeEntity();
    entity3->addComponent(sortOrder3);

    frts::BlockImplPtr blockImpl = frts::makeBlock(
                frts::makeId(frts::ComponentIds::blocking()),
                frts::makeId(frts::ComponentIds::sortOrder()));
    frts::BlockPtr block = blockImpl;

    blockImpl->insert(entity1);
    blockImpl->insert(entity2);
    blockImpl->insert(entity3);

    auto sortEntities = block->getByComponent(sort);
    REQUIRE(sortEntities.size() == 3);
    auto it = sortEntities.begin();
    REQUIRE(*it == entity3);
    std::advance(it, 1);
    REQUIRE(*it == entity1);
    std::advance(it, 1);
    REQUIRE(*it == entity2);
}
