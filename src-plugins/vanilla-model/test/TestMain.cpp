#include <catch.hpp>

#include "LogStub.h"

#include <entity/ComponentIds.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/HasResourceImpl.h>
#include <entity/impl/IsResourceImpl.h>
#include <main/impl/ModelFactoryImpl.h>
#include <main/impl/RegionManagerImpl.h>
#include <region/impl/PointImpl.h>
#include <region/impl/RegionGeneratorImpl.h>
#include <region/impl/RegionImpl.h>
#include <resource/impl/DistanceAlgorithmImpl.h>
#include <resource/impl/LockableHasResourceManagerImpl.h>
#include <resource/impl/LockableIsResourceManagerImpl.h>

#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <memory>


TEST_CASE("MainFactory.", "[main]")
{
    frts::LogPtr log = std::make_shared<TestLog>();
    frts::SharedManagerPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

    frts::ModelFactoryPtr modelFactory = frts::makeModelFactory();

    SECTION("Build components.")
    {
        modelFactory->createData(shared);
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
        REQUIRE(entity->getComponents().empty());
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
    frts::LogPtr log = std::make_shared<TestLog>();
    frts::SharedManagerPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

    frts::Point::value sizeX = 10;
    frts::Point::value sizeY = 10;
    frts::RegionGeneratorPtr regionGenerator = frts::makeRegionGenerator(frts::makeId(frts::ComponentIds::blocking()),
                                                                         frts::makeId(frts::ComponentIds::sortOrder()),
                                                                         sizeX, sizeY);
    frts::RegionPtr region = frts::makeRegion(sizeX, sizeY, regionGenerator);

    frts::DistanceAlgorithmPtr distAlgo = frts::makeDistanceAlgorithm();
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
        regionManager->setPos(entity, pos);
        REQUIRE(regionManager->getChangedPos().size() == 2);

        pos = frts::makePoint(0, 0, 0);
        regionManager->addChangedPos(pos);
        REQUIRE(regionManager->getChangedPos().size() == 2);

        regionManager->resetChangedPos();
        REQUIRE(regionManager->getChangedPos().empty());

        regionManager->removeEntity(entity);
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
        regionManager->setPos(entity, pos);

        frts::ResourceLockPtr lock = regionManager->findNearestResource(entityType, resourceId, pos);
        REQUIRE(lock != nullptr);
        REQUIRE(lock->getEntity() == entity);
        REQUIRE(lock->getResourceType() == resourceId);
        REQUIRE(lock->isValid());
        REQUIRE(regionManager->getPos(lock->getEntity()) == pos);
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
        regionManager->setPos(entity, pos);

        frts::ResourceLockPtr lock = regionManager->findNearestResourceEntity(entityType, resourceId, pos);
        REQUIRE(lock != nullptr);
        REQUIRE(lock->getEntity() == entity);
        REQUIRE(lock->getResourceType() == resourceId);
        REQUIRE(lock->isValid());
        REQUIRE(regionManager->getPos(lock->getEntity()) == pos);
    }
}
