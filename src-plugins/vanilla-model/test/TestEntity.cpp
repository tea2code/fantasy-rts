#include <catch.hpp>

#include <entity/ComponentIds.h>
#include <entity/impl/BlockedByImpl.h>
#include <entity/impl/BlockedByBuilder.h>
#include <entity/impl/BlockingImpl.h>
#include <entity/impl/BlockingBuilder.h>
#include <entity/impl/CurriculumBuilder.h>
#include <entity/impl/CurriculumImpl.h>
#include <entity/impl/DropImpl.h>
#include <entity/impl/DropBuilder.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/HasResourceImpl.h>
#include <entity/impl/HasResourceBuilder.h>
#include <entity/impl/IsResourceImpl.h>
#include <entity/impl/IsResourceBuilder.h>
#include <entity/impl/InfoImpl.h>
#include <entity/impl/InfoBuilder.h>
#include <entity/impl/MovableBuilder.h>
#include <entity/impl/MovableImpl.h>
#include <entity/impl/SortOrderImpl.h>
#include <entity/impl/SortOrderBuilder.h>
#include <entity/impl/TeleportBuilder.h>
#include <entity/impl/TeleportImpl.h>
#include <region/impl/BlockImpl.h>
#include <region/impl/PointImpl.h>
#include <pathfinding/impl/PathImpl.h>

#include <frts/configuration>
#include <log/NoLog.h>
#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <string>
#include <vector>



namespace TestEntity
{
    class StringListConfig : public frts::ConfigNode
    {
    public:
        StringListConfig(const std::string& key, const std::vector<std::string>& values)
            : key{key}, values{values}
        {}

        Iterator begin() { return Iterator(nullptr); }
        Iterator end() { return Iterator(nullptr); }

        bool getBool(const std::string&) { return false; }
        bool getBool(const std::string&, bool) { return false; }
        std::vector<bool> getBools(const std::string&) { return {}; }

        double getFloat(const std::string&) { return 0.0; }
        double getFloat(const std::string&, double) { return 0.0; }
        std::vector<double> getFloats(const std::string&) { return {}; }

        long getInteger(const std::string&) { return 0; }
        long getInteger(const std::string&, long) { return 0; }
        std::vector<long> getIntegers(const std::string&) { return {}; }

        frts::ConfigNodePtr getNode(const std::string&) { return nullptr; }

        std::string getString(const std::string&) { return ""; }
        std::string getString(const std::string&, const std::string&) { return ""; }
        std::vector<std::string> getStrings(const std::string& key) { return key == this->key ? values : std::vector<std::string>(); }

        bool has(const std::string&) { return false; }

        bool isBool(const std::string&) { return false; }
        bool isFloat(const std::string&) { return false; }
        bool isInteger(const std::string&) { return false; }
        bool isString(const std::string&) { return false; }

    private:
        std::string key;
        std::vector<std::string> values;
    };

    class IsResourceConfig : public frts::ConfigNode
    {
    public:
        Iterator begin() { return Iterator(nullptr); }
        Iterator end() { return Iterator(nullptr); }

        bool getBool(const std::string&) { return false; }
        bool getBool(const std::string&, bool) { return false; }
        std::vector<bool> getBools(const std::string&) { return {}; }

        double getFloat(const std::string&) { return 0.0; }
        double getFloat(const std::string&, double) { return 0.0; }
        std::vector<double> getFloats(const std::string&) { return {}; }

        long getInteger(const std::string&) { return 0; }
        long getInteger(const std::string&, long) { return 0; }
        std::vector<long> getIntegers(const std::string&) { return {}; }

        frts::ConfigNodePtr getNode(const std::string&) { return nullptr; }

        std::string getString(const std::string& key) { return key == "resource_type" ? "id.resource" : ""; }
        std::string getString(const std::string&, const std::string&) { return ""; }
        std::vector<std::string> getStrings(const std::string&) { return {}; }

        bool has(const std::string&) { return false; }

        bool isBool(const std::string&) { return false; }
        bool isFloat(const std::string&) { return false; }
        bool isInteger(const std::string&) { return false; }
        bool isString(const std::string&) { return false; }
    };

    class SortOrderConfig : public frts::ConfigNode
    {
    public:
        Iterator begin() { return Iterator(nullptr); }
        Iterator end() { return Iterator(nullptr); }

        bool getBool(const std::string&) { return false; }
        bool getBool(const std::string&, bool) { return false; }
        std::vector<bool> getBools(const std::string&) { return {}; }

        double getFloat(const std::string&) { return 0.0; }
        double getFloat(const std::string&, double) { return 0.0; }
        std::vector<double> getFloats(const std::string&) { return {}; }

        long getInteger(const std::string& key) { return key == "sort_order" ? 123 : 0; }
        long getInteger(const std::string&, long) { return 0; }
        std::vector<long> getIntegers(const std::string&) { return {}; }

        frts::ConfigNodePtr getNode(const std::string&) { return nullptr; }

        std::string getString(const std::string&) { return ""; }
        std::string getString(const std::string&, const std::string&) { return ""; }
        std::vector<std::string> getStrings(const std::string&) { return {}; }

        bool has(const std::string&) { return false; }

        bool isBool(const std::string&) { return false; }
        bool isFloat(const std::string&) { return false; }
        bool isInteger(const std::string&) { return false; }
        bool isString(const std::string&) { return false; }
    };
}

TEST_CASE("Blocking/BlockedBy.", "[entity]")
{
    auto block1a = frts::makeId("block1");
    auto block1b = frts::makeId("block1");
    auto block2 = frts::makeId("block2");

    auto blockedBy1 = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy1->addBlock(block1a);
    auto blockedBy2 = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy2->addBlock(block2);
    auto blocking = frts::makeBlocking(frts::makeId(frts::ComponentIds::blocking()));
    blocking->addBlock(block1b);

    REQUIRE(blocking->blocks(blockedBy1));
    REQUIRE_FALSE(blocking->blocks(blockedBy2));
}

TEST_CASE("BlockedBy Builder.", "[entity]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeBlockedByBuilder();

    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto configNode = std::make_shared<TestEntity::StringListConfig>("blocks", std::vector<std::string> {"block1", "block2"});
    component = builder->build(shared, configNode);
    REQUIRE(component != nullptr);
    auto castComponent = std::static_pointer_cast<frts::BlockedBy>(component);
    REQUIRE(castComponent->getBlocks().size() == 2);
}

TEST_CASE("Blocking Builder.", "[entity]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeBlockingBuilder();

    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto configNode = std::make_shared<TestEntity::StringListConfig>("blocks", std::vector<std::string> {"block1", "block2"});
    component = builder->build(shared, configNode);
    REQUIRE(component != nullptr);

    auto blockedBy = frts::makeBlockedBy(frts::makeId(frts::ComponentIds::blockedBy()));
    blockedBy->addBlock(frts::makeId("block1"));

    auto castComponent = std::static_pointer_cast<frts::Blocking>(component);
    //REQUIRE(castComponent->blocks(blockedBy));
}

TEST_CASE("Curriculum.", "[entity]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeCurriculumBuilder();
    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto ability1 = shared->makeId("ability.1");
    auto ability2 = shared->makeId("ability.2");
    auto ability3 = shared->makeId("ability.3");

    auto castComponent = std::static_pointer_cast<frts::Curriculum>(component);
    castComponent->addAbility(ability1);
    castComponent->addAbility(ability2);

    REQUIRE(castComponent->getAbilities().size() == 2);
    REQUIRE(castComponent->hasAbility(ability1));
    REQUIRE(castComponent->hasAbility(ability2));
    REQUIRE_FALSE(castComponent->hasAbility(ability3));

    castComponent->removeAbility(ability1);

    REQUIRE(castComponent->getAbilities().size() == 1);
    REQUIRE_FALSE(castComponent->hasAbility(ability1));
    REQUIRE(castComponent->hasAbility(ability2));
    REQUIRE_FALSE(castComponent->hasAbility(ability3));
}

TEST_CASE("Drop.", "[entity]")
{
    frts::EntityPtr entity = frts::makeEntity();
    frts::IdPtr resourceId1 = frts::makeId("wood");
    frts::IdPtr resourceId2 = frts::makeId("food");

    frts::DropPtr drop = frts::makeDrop(frts::makeId(frts::ComponentIds::drop()));
    drop->addDrop(resourceId1);
    frts::IdPtr id = drop->getComponentType();
    entity->addComponent(drop);

    frts::DropPtr foundDrop = frts::getComponent<frts::Drop>(id, entity);
    REQUIRE(foundDrop != nullptr);
    REQUIRE(foundDrop->hasDrop(resourceId1));
    REQUIRE_FALSE(foundDrop->hasDrop(resourceId2));
    REQUIRE(foundDrop->getDrops().size() == 1);

    foundDrop->addDrop(resourceId2);

    REQUIRE(foundDrop->hasDrop(resourceId1));
    REQUIRE(foundDrop->hasDrop(resourceId2));
    REQUIRE(foundDrop->getDrops().size() == 2);

    foundDrop->removeDrop(resourceId1);

    REQUIRE_FALSE(foundDrop->hasDrop(resourceId1));
    REQUIRE(foundDrop->hasDrop(resourceId2));
    REQUIRE(foundDrop->getDrops().size() == 1);
}

TEST_CASE("Drop Builder.", "[entity]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeDropBuilder();

    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto configNode = std::make_shared<TestEntity::StringListConfig>("drops", std::vector<std::string> {"drop1", "drop2"});
    component = builder->build(shared, configNode);
    REQUIRE(component != nullptr);
    auto castComponent = std::static_pointer_cast<frts::Drop>(component);
    REQUIRE(castComponent->getDrops().size() == 2);
    REQUIRE(castComponent->hasDrop(frts::makeId("drop1")));
    REQUIRE(castComponent->hasDrop(frts::makeId("drop2")));
    REQUIRE_FALSE(castComponent->hasDrop(frts::makeId("drop3")));
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

    entity->addComponent(component);
    entity->addComponent(component);

    frts::HasResourcePtr hasResource = frts::makeHasResource(frts::makeId(frts::ComponentIds::hasResource()));
    entity->addComponent(hasResource);

    REQUIRE(entity->getComponents().size() == 2);
}

TEST_CASE("Resource.", "[entity]")
{
    frts::EntityPtr entity = frts::makeEntity();
    frts::IdPtr resourceId1 = frts::makeId("wood");
    frts::IdPtr resourceId2 = frts::makeId("food");

    frts::HasResourcePtr hasResource = frts::makeHasResource(frts::makeId(frts::ComponentIds::hasResource()));
    hasResource->addResource(resourceId1);
    frts::IdPtr id = hasResource->getComponentType();
    entity->addComponent(hasResource);

    frts::HasResourcePtr foundHasResource = frts::getComponent<frts::HasResource>(id, entity);
    REQUIRE(foundHasResource != nullptr);
    REQUIRE(foundHasResource->hasResource(resourceId1));
    REQUIRE_FALSE(foundHasResource->hasResource(resourceId2));
    REQUIRE(foundHasResource->getResources().size() == 1);

    foundHasResource->addResource(resourceId2);

    REQUIRE(foundHasResource->hasResource(resourceId1));
    REQUIRE(foundHasResource->hasResource(resourceId2));
    REQUIRE(foundHasResource->getResources().size() == 2);

    foundHasResource->removeResource(resourceId1);

    REQUIRE_FALSE(foundHasResource->hasResource(resourceId1));
    REQUIRE(foundHasResource->hasResource(resourceId2));
    REQUIRE(foundHasResource->getResources().size() == 1);

    frts::IsResourcePtr isResource = frts::makeIsResource(frts::makeId(frts::ComponentIds::isResource()));
    isResource->setResourceType(resourceId1);
    id = isResource->getComponentType();
    entity->addComponent(isResource);

    frts::IsResourcePtr foundIsResource = frts::getComponent<frts::IsResource>(id, entity);
    REQUIRE(foundIsResource != nullptr);
    REQUIRE(foundIsResource->getResourceType() == resourceId1);
}

TEST_CASE("HasResource Builder.", "[entity]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeHasResourceBuilder();

    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto configNode = std::make_shared<TestEntity::StringListConfig>("resources", std::vector<std::string> {"resource1", "resource2"});
    component = builder->build(shared, configNode);
    REQUIRE(component != nullptr);
    auto castComponent = std::static_pointer_cast<frts::HasResource>(component);
    REQUIRE(castComponent->getResources().size() == 2);
    REQUIRE(castComponent->hasResource(frts::makeId("resource1")));
    REQUIRE(castComponent->hasResource(frts::makeId("resource2")));
    REQUIRE_FALSE(castComponent->hasResource(frts::makeId("resource3")));
}

TEST_CASE("IsResource Builder.", "[entity]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeIsResourceBuilder();

    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto configNode = std::make_shared<TestEntity::IsResourceConfig>();
    component = builder->build(shared, configNode);
    REQUIRE(component != nullptr);
    auto castComponent = std::static_pointer_cast<frts::IsResource>(component);
    REQUIRE(castComponent->getResourceType() == frts::makeId("id.resource"));
}

TEST_CASE("Info.", "[entity]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeInfoBuilder();
    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto k1 = shared->makeId("k1");
    auto v1 = shared->makeId("v1");
    auto k2 = shared->makeId("k2");
    auto v2 = shared->makeId("v2");
    std::vector<frts::Info::InfoItem> infos;
    infos.push_back(std::make_pair(k1, v1));
    infos.push_back(std::make_pair(k2, v2));

    auto info = std::static_pointer_cast<frts::Info>(component);
    info->setInformation(infos);

    auto componentInfos = info->getInformation();
    REQUIRE(componentInfos.size() == 2);
    REQUIRE(componentInfos.at(0).first == k1);
    REQUIRE(componentInfos.at(0).second == v1);
    REQUIRE(componentInfos.at(1).first == k2);
    REQUIRE(componentInfos.at(1).second == v2);
}

TEST_CASE("Movable.", "[entity]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeMovableBuilder();
    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    // Without path.
    auto movable = std::static_pointer_cast<frts::Movable>(component);
    REQUIRE(movable->getNextPathPos() == nullptr);
    REQUIRE(movable->getPreviousPathPos() == nullptr);

    // With path.
    frts::Path::PathPart pathPart = {
        frts::makePoint(0, 0, 0),
        frts::makePoint(1, 0, 0),
        frts::makePoint(1, 1, 0),
        frts::makePoint(1, 0, 0)
    };
   auto path = frts::makePath(pathPart, true);
    movable->setPath(path);
    REQUIRE(movable->getPath()->getCompletePath() == pathPart);
    REQUIRE(movable->getPreviousPathPos() == nullptr);
    REQUIRE(movable->getNextPathPos() == frts::makePoint(1, 0, 0));
    REQUIRE(movable->getDirection() == frts::Movable::Direction::East);
    REQUIRE(movable->getPreviousPathPos() == frts::makePoint(0, 0, 0));
    REQUIRE(movable->getNextPathPos() == frts::makePoint(1, 1, 0));
    REQUIRE(movable->getDirection() == frts::Movable::Direction::South);
    REQUIRE(movable->getNextPathPos() == frts::makePoint(1, 0, 0));
    REQUIRE(movable->getDirection() == frts::Movable::Direction::North);
    REQUIRE(movable->getNextPathPos() == nullptr);
    REQUIRE(movable->getDirection() == frts::Movable::Direction::South);
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

TEST_CASE("Sort Order Builder.", "[entity]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeSortOrderBuilder();

    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto configNode = std::make_shared<TestEntity::SortOrderConfig>();
    component = builder->build(shared, configNode);
    REQUIRE(component != nullptr);
    auto castComponent = std::static_pointer_cast<frts::SortOrder>(component);
    REQUIRE(castComponent->getSortOrder() == 123);
}

TEST_CASE("Teleport.", "[entity]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeTeleportBuilder();
    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    auto teleport = std::static_pointer_cast<frts::Teleport>(component);
    auto entity = frts::makeEntity();
    teleport->setTarget(entity);
    REQUIRE(teleport->getTarget() == entity);
}
