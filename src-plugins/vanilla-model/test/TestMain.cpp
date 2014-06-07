#include <catch.hpp>

#include "LogStub.h"

#include <entity/ComponentIds.h>
#include <main/impl/ModelFactoryImpl.h>

#include <shared/impl/SharedManagerImpl.h>

#include <memory>


TEST_CASE("MainFactory.", "[main]")
{
    frts::LogPtr log = std::make_shared<TestLog>();
    frts::SharedManagerPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

    frts::ModelFactoryPtr modelFactory = frts::makeModelFactory();

    SECTION("Build components.")
    {
        modelFactory->init(shared);

        frts::IdPtr id = shared->makeId(frts::ComponentIds::blockedBy());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::blocking());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::hasResource());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::isResource());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::sortOrder());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);
    }

    SECTION("Build empty entity.")
    {
        frts::EntityPtr entity = modelFactory->makeEntity();
        REQUIRE(entity->getComponents().size() == 0);
    }

    SECTION("Build points.")
    {
        frts::PointPtr point = modelFactory->makePoint(1, 2, 3);
        REQUIRE(point->getX() == 1);
        REQUIRE(point->getY() == 2);
        REQUIRE(point->getZ() == 3);
    }
}

TEST_CASE("RegionManager.", "[main]")
{

}
