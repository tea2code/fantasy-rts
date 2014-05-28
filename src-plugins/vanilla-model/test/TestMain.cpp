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

    frts::ModelFactoryPtr modelFactory = std::make_shared<frts::ModelFactoryImpl>();

    SECTION("Build components.")
    {
        modelFactory->init(shared);

        frts::IdPtr id = shared->makeId(frts::ComponentIds::blockedBy());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::blocking());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::sortOrder());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);
    }
}
