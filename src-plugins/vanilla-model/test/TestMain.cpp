#include <catch.hpp>

#include "TestRegionGenerator.h"

#include <entity/ComponentIds.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/HasResourceImpl.h>
#include <entity/impl/IsResourceImpl.h>
#include <main/impl/ModelDataImpl.h>
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
#include <thread>



TEST_CASE("ModelData.", "[main]")
{
    frts::ModelDataPtr modelData = frts::makeModelData();

    modelData->setMapSizeX(1);
    modelData->setMapSizeY(2);
    modelData->setPrecalculateDown(3);
    modelData->setPrecalculateUp(4);
    modelData->setSurfaceZLevel(5);
    modelData->setPrecalculatedRange(std::make_pair(6, 7));

    REQUIRE(modelData->getMapSizeX() == 1);
    REQUIRE(modelData->getMapSizeY() == 2);
    REQUIRE(modelData->getPrecalculateDown() == 3);
    REQUIRE(modelData->getPrecalculateUp() == 4);
    REQUIRE(modelData->getSurfaceZLevel() == 5);
    REQUIRE(modelData->getPrecalculatedRange() == std::make_pair(6, 7));
}

TEST_CASE("ModelFactory.", "[main]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);
    shared->setDataValue(shared->makeId(frts::MainIds::mainData()), frts::makeMainData("/", frts::fromMilliseconds(10)));

    frts::ModelFactoryPtr modelFactory = frts::makeModelFactory();

    SECTION("Build components.")
    {
        // Execute init() twice because it waits one run.
        modelFactory->preInit(shared);
        modelFactory->createData(shared);
        modelFactory->init(shared);
        modelFactory->init(shared);

        auto entity = frts::makeEntity();

        frts::IdPtr id = shared->makeId(frts::ComponentIds::blockedBy());
        REQUIRE(modelFactory->makeComponent(id, entity, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::blocking());
        REQUIRE(modelFactory->makeComponent(id, entity, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::drop());
        REQUIRE(modelFactory->makeComponent(id, entity, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::hasResource());
        REQUIRE(modelFactory->makeComponent(id, entity, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::isResource());
        REQUIRE(modelFactory->makeComponent(id, entity, shared)->getComponentType() == id);

        id = shared->makeId(frts::ComponentIds::sortOrder());
        REQUIRE(modelFactory->makeComponent(id, entity, shared)->getComponentType() == id);

        // TODO Test all components.
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
    shared->setDataValue(shared->makeId(frts::MainIds::mainData()), frts::makeMainData("/", frts::fromMilliseconds(10)));

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
    frts::RegionPtr region = frts::makeRegion(regionGenerator);

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

    SECTION("Thread safety.")
    {
        std::vector<frts::BlockPtr> thread1Blocks;
        std::vector<frts::BlockPtr> thread2Blocks;

        auto func = [&](std::vector<frts::BlockPtr>& blocks)
        {
            for (int x = 0; x < sizeX; ++x)
            {
                for (int y = 0; y < sizeY; ++y)
                {
                    blocks.push_back(regionManager->getBlock(frts::makePoint(x, y, 0), shared));
                }
            }
        };

        std::thread thread1(func, std::ref(thread1Blocks));
        std::thread thread2(func, std::ref(thread2Blocks));

        thread1.join();
        thread2.join();

        auto size = static_cast<unsigned int>(sizeX * sizeY);

        REQUIRE(thread1Blocks.size() == size);
        REQUIRE(thread2Blocks.size() == size);

        for (unsigned int i = 0; i < size; ++i)
        {
            REQUIRE(thread1Blocks.at(i) == thread2Blocks.at(i));
        }
    }
}
