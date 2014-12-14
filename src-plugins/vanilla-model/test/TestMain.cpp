#include <catch.hpp>

#include "TestRegionGenerator.h"

#include <entity/ComponentIds.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/HasResourceImpl.h>
#include <entity/impl/IsResourceImpl.h>
#include <main/impl/ModelFactoryImpl.h>
#include <main/impl/RegionManagerImpl.h>
#include <main/ModelError.h>
#include <main/ModelIds.h>
#include <main/ModelReseter.h>
#include <region/impl/PointImpl.h>
#include <region/impl/RegionImpl.h>
#include <pathfinding/impl/EuclideanDistance.h>
#include <resource/impl/LockableHasResourceManager.h>
#include <resource/impl/LockableIsResourceManager.h>

#include <log/NoLog.h>
#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>
#include <shared/impl/MainDataImpl.h>

#include <memory>


TEST_CASE("ModelFactory.", "[main]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);
    shared->setDataValue(shared->makeId(frts::MainIds::mainData()), frts::makeMainData("/"));

    frts::ModelFactoryPtr modelFactory = frts::makeModelFactory();

    SECTION("Build components.")
    {
        // Execute init() twice because it waits one run.
        modelFactory->preInit(shared);
        modelFactory->createData(shared);
        modelFactory->init(shared);
        modelFactory->init(shared);

        frts::IdPtr id = shared->makeId(frts::ComponentIds::blockedBy());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::blocking());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::drop());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::hasResource());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::isResource());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::sortOrder());
        REQUIRE(modelFactory->makeComponent(id, shared)->getComponentType() == id);
    }

    SECTION("Get path finder.")
    {
        // Execute init() twice because it waits one run.
        modelFactory->preInit(shared);
        modelFactory->createData(shared);
        modelFactory->init(shared);
        modelFactory->init(shared);

        REQUIRE(modelFactory->getPathFinder() != nullptr);
    }

    SECTION("Build empty entity.")
    {
        frts::EntityPtr entity = modelFactory->makeEntity();
        REQUIRE(entity->getComponents().empty());
    }

    SECTION("Build entity.")
    {
        frts::IdPtr id = frts::makeId("not.existing.entity.id");
        REQUIRE_THROWS_AS(modelFactory->makeEntity(id, shared), frts::UnknownEntityError);
    }

    SECTION("Build points.")
    {
        frts::PointPtr point = modelFactory->makePoint(1, 2, 3);
        REQUIRE(point->getX() == 1);
        REQUIRE(point->getY() == 2);
        REQUIRE(point->getZ() == 3);
    }
}

TEST_CASE("ModelReseter.", "[main]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);
    shared->setDataValue(shared->makeId(frts::MainIds::mainData()), frts::makeMainData("/"));

    frts::TickablePtr modelReseter = frts::makeModelReseter();

    // Execute init() twice because it waits one run.
    frts::ModelFactoryPtr modelFactory = frts::makeModelFactory();
    modelFactory->preInit(shared);
    modelFactory->createData(shared);
    modelFactory->init(shared);
    modelFactory->init(shared);
    REQUIRE_NOTHROW(modelReseter->validateData(shared));

    frts::IdPtr regionManagerId = shared->makeId(frts::ModelIds::regionManager());
    frts::RegionManagerPtr regionManager = std::static_pointer_cast<frts::RegionManager>(shared->getDataValue(regionManagerId));
    regionManager->addChangedPos(frts::makePoint(0, 0, 0));
    REQUIRE(regionManager->getChangedPos().size() == 1);

    modelReseter->tick(shared);
    REQUIRE(regionManager->getChangedPos().empty());
}

TEST_CASE("RegionManager.", "[main]")
{
    frts::LogPtr log = frts::makeNoLog();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);

    frts::Point::value sizeX = 10;
    frts::Point::value sizeY = 10;
    auto regionGenerator = test::makeSimpleTestRegionGenerator(frts::makeId(frts::ComponentIds::blocking()),
                                                               frts::makeId(frts::ComponentIds::sortOrder()));
    frts::RegionPtr region = frts::makeRegion(sizeX, sizeY, regionGenerator);

    frts::DistanceAlgorithmPtr distAlgo = frts::makeEuclideanDistance();
    frts::IdPtr hasResourceType = frts::makeId(frts::ComponentIds::hasResource());
    frts::LockableResourceManagerPtr resourceEntityManager = frts::makeLockableHasResourceManager(hasResourceType, region, distAlgo);
    frts::IdPtr isResourceType = frts::makeId(frts::ComponentIds::isResource());
    frts::LockableResourceManagerPtr resourceManager = frts::makeLockableIsResourceManager(isResourceType, region, distAlgo);

    frts::RegionManagerPtr regionManager = frts::makeRegionManager(
                region, resourceManager, resourceEntityManager, hasResourceType,
                isResourceType);

    SECTION("Changed positions.")
    {
        REQUIRE(regionManager->getChangedPos().empty());

        frts::PointPtr pos = frts::makePoint(0, 0, 0);
        regionManager->addChangedPos(pos);
        REQUIRE(regionManager->getChangedPos().size() == 1);

        frts::EntityPtr entity = frts::makeEntity();
        pos = frts::makePoint(0, 1, 0);
        regionManager->setPos(entity, pos, shared);
        REQUIRE(regionManager->getChangedPos().size() == 2);

        pos = frts::makePoint(0, 0, 0);
        regionManager->addChangedPos(pos);
        REQUIRE(regionManager->getChangedPos().size() == 2);

        regionManager->resetChangedPos();
        REQUIRE(regionManager->getChangedPos().empty());

        regionManager->removeEntity(entity, shared);
        REQUIRE(regionManager->getChangedPos().size() == 1);
    }

    SECTION("Find resource.")
    {
        frts::IdPtr entityType = frts::makeId("entityType1");
        frts::EntityPtr entity = frts::makeEntity();
        frts::PointPtr pos = frts::makePoint(0, 0, 0);

        frts::IdPtr componentType = frts::makeId(frts::ComponentIds::isResource());
        frts::IsResourcePtr component = frts::makeIsResource(componentType);
        frts::IdPtr resourceId = frts::makeId("wood");
        component->setResourceType(resourceId);

        entity->addComponent(component);
        regionManager->setPos(entity, pos, shared);

        frts::ResourceLockPtr lock = regionManager->findNearestResource(entityType, resourceId, pos, shared);
        REQUIRE(lock != nullptr);
        REQUIRE(lock->getEntity() == entity);
        REQUIRE(lock->getResourceType() == resourceId);
        REQUIRE(lock->isValid());
        REQUIRE(regionManager->getPos(lock->getEntity(), shared) == pos);
    }

    SECTION("Find resource entity.")
    {
        frts::IdPtr entityType = frts::makeId("entityType1");
        frts::EntityPtr entity = frts::makeEntity();
        frts::PointPtr pos = frts::makePoint(0, 0, 0);

        frts::IdPtr componentType = frts::makeId(frts::ComponentIds::hasResource());
        frts::HasResourcePtr component = frts::makeHasResource(componentType);
        frts::IdPtr resourceId = frts::makeId("wood");
        component->addResource(resourceId);

        entity->addComponent(component);
        regionManager->setPos(entity, pos, shared);

        frts::ResourceLockPtr lock = regionManager->findNearestResourceEntity(entityType, resourceId, pos, shared);
        REQUIRE(lock != nullptr);
        REQUIRE(lock->getEntity() == entity);
        REQUIRE(lock->getResourceType() == resourceId);
        REQUIRE(lock->isValid());
        REQUIRE(regionManager->getPos(lock->getEntity(), shared) == pos);
    }
}
