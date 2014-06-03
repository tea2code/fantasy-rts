#include <catch.hpp>

#include <entity/ComponentIds.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/HasResourceImpl.h>
#include <entity/impl/IsResourceImpl.h>
#include <region/RegionGenerator.h>
#include <region/impl/BlockImpl.h>
#include <region/impl/PointImpl.h>
#include <region/impl/RegionImpl.h>
#include <resource/impl/DistanceAlgorithmImpl.h>
#include <resource/impl/LockableHasResourceManagerImpl.h>
#include <resource/impl/LockableIsResourceManagerImpl.h>
#include <resource/impl/ResourceLockImpl.h>

#include <shared/impl/IdImpl.h>

#include <memory>


namespace frts
{
    class TestRegionGenerator : public RegionGenerator
    {
    public:
        TestRegionGenerator()
            : blockingType{makeId(ComponentIds::blocking())},
              sortOrderType{makeId(ComponentIds::sortOrder())}
        {}

        std::map<PointPtr, WriteableBlockPtr> allBlocks(Point::value zLevel) override
        {
            const int sizeX = 10;
            const int sizeY = 10;

            std::map<PointPtr, WriteableBlockPtr> result;
            for (int x = 0; x < sizeX; ++x)
            {
                for (int y = 0; y < sizeY; ++y)
                {
                    result[makePoint(x, y, zLevel)] = makeBlock(blockingType, sortOrderType);
                }
            }
            return result;
        }

        WriteableBlockPtr newBlock(PointPtr) override
        {
            return makeBlock(blockingType, sortOrderType);
        }

    private:
        IdPtr blockingType;
        IdPtr sortOrderType;
    };
}

TEST_CASE("LockableResourceManager.", "[resource]")
{
    frts::IdPtr entityType1 = frts::makeId("entityType1");
    frts::IdPtr entityType2 = frts::makeId("entityType2");

    frts::EntityPtr entity1 = frts::makeEntity();
    frts::EntityPtr entity2 = frts::makeEntity();
    frts::EntityPtr entity3 = frts::makeEntity();
    frts::EntityPtr entity4 = frts::makeEntity();

    frts::PointPtr pos1 = frts::makePoint(0, 5, 0);
    frts::PointPtr pos2 = frts::makePoint(5, 0, 0);
    frts::PointPtr pos3 = frts::makePoint(1, 2, 0);
    frts::PointPtr pos4 = frts::makePoint(5, 5, 0);
    frts::PointPtr pos5 = frts::makePoint(0, 0, 0);

    frts::IdPtr resourceId1 = frts::makeId("wood");
    frts::IdPtr resourceId2 = frts::makeId("food");
    frts::IdPtr resourceId3 = frts::makeId("iron");

    frts::RegionGeneratorPtr regionGenerator = std::make_shared<frts::TestRegionGenerator>();
    frts::RegionPtr region = frts::makeRegion(10, 10, regionGenerator);

    region->setPos(entity1, pos1);
    region->setPos(entity2, pos2);
    region->setPos(entity3, pos3);
    region->setPos(entity4, pos4);

    frts::DistanceAlgorithmPtr distAlgo = frts::makeDistanceAlgorithm();

    SECTION("With HasResource")
    {
        frts::IdPtr componentType = frts::makeId(frts::ComponentIds::hasResource());

        frts::HasResourcePtr component1 = frts::makeHasResource(componentType);
        component1->addResource(resourceId1);
        frts::HasResourcePtr component2 = frts::makeHasResource(componentType);
        component2->addResource(resourceId2);

        entity1->addComponent(component1);
        entity2->addComponent(component2);
        // entity3 doesn't get a resource.
        entity4->addComponent(component1);

        frts::LockableResourceManagerPtr resourceManager = frts::makeLockableHasResourceManager(componentType, region, distAlgo);

        resourceManager->add(entity1);
        resourceManager->add(entity2);
        resourceManager->add(entity3);
        resourceManager->add(entity4);

        frts::ResourceLockPtr lock1 = resourceManager->findNearest(entityType1, resourceId3, pos5);
        REQUIRE(lock1 == nullptr);

        frts::ResourceLockPtr lock2 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock2 != nullptr);
        REQUIRE(lock2->getEntity() == entity1);
        REQUIRE(lock2->getResourceType() == resourceId1);
        REQUIRE(lock2->isValid());
        REQUIRE(region->getPos(lock2->getEntity()) == pos1);

        frts::ResourceLockPtr lock3 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock3 != nullptr);
        REQUIRE(lock3->getEntity() == entity4);
        REQUIRE(lock3->getResourceType() == resourceId1);
        REQUIRE(lock3->isValid());
        REQUIRE(region->getPos(lock3->getEntity()) == pos4);

        frts::ResourceLockPtr lock4 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock4 == nullptr);

        frts::ResourceLockPtr lock5 = resourceManager->findNearest(entityType2, resourceId1, pos5);
        REQUIRE(lock5 != nullptr);
        REQUIRE(lock5->getEntity() == entity1);
        REQUIRE(lock5->getResourceType() == resourceId1);
        REQUIRE(lock5->isValid());
        REQUIRE(region->getPos(lock5->getEntity()) == pos1);

        lock2->release();
        REQUIRE(lock2->getEntity() == nullptr);
        REQUIRE(lock2->getResourceType() == nullptr);
        REQUIRE_FALSE(lock2->isValid());

        lock2 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock2 != nullptr);
        REQUIRE(lock2->getEntity() == entity1);
        REQUIRE(lock2->getResourceType() == resourceId1);
        REQUIRE(lock2->isValid());
        REQUIRE(region->getPos(lock2->getEntity()) == pos1);

        resourceManager->remove(entity1);
        REQUIRE(lock2->getEntity() == nullptr);
        REQUIRE(lock2->getResourceType() == nullptr);
        REQUIRE_FALSE(lock2->isValid());
        REQUIRE(lock5->getEntity() == nullptr);
        REQUIRE(lock5->getResourceType() == nullptr);
        REQUIRE_FALSE(lock5->isValid());

        lock2 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock2 == nullptr);

        frts::ResourceLockPtr lock6 = resourceManager->findNearest(entityType1, resourceId2, pos5);
        REQUIRE(lock6 != nullptr);
        REQUIRE(lock6->getEntity() == entity2);
        REQUIRE(lock6->getResourceType() == resourceId2);
        REQUIRE(lock6->isValid());
        REQUIRE(region->getPos(lock5->getEntity()) == pos1);
    }

    /*
    SECTION("With IsResource.")
    {
        frts::IdPtr componentType = frts::makeId(frts::ComponentIds::isResource());

        frts::IsResourcePtr component1 = frts::makeIsResource(componentType);
        component1->setResourceType(resourceId1);
        frts::IsResourcePtr component2 = frts::makeIsResource(componentType);
        component2->setResourceType(resourceId2);

        entity1->addComponent(component1);
        entity2->addComponent(component2);
        // entity3 doesn't get a resource.
        entity4->addComponent(component1);

        frts::LockableResourceManagerPtr resourceManager = frts::makeLockableIsResourceManager(componentType, region, distAlgo);

        resourceManager->add(entity1);
        resourceManager->add(entity2);
        resourceManager->add(entity3);
        resourceManager->add(entity4);

        frts::ResourceLockPtr lock1 = resourceManager->findNearest(entityType1, resourceId3, pos5);
        REQUIRE(lock1 == nullptr);

        frts::ResourceLockPtr lock2 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock2 != nullptr);
        REQUIRE(lock2->getEntity() == entity1);
        REQUIRE(lock2->getResourceType() == resourceId1);
        REQUIRE(lock2->isValid());
        REQUIRE(region->getPos(lock2->getEntity()) == pos1);

        frts::ResourceLockPtr lock3 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock3 != nullptr);
        REQUIRE(lock3->getEntity() == entity4);
        REQUIRE(lock3->getResourceType() == resourceId1);
        REQUIRE(lock3->isValid());
        REQUIRE(region->getPos(lock3->getEntity()) == pos4);

        frts::ResourceLockPtr lock4 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock4 == nullptr);

        frts::ResourceLockPtr lock5 = resourceManager->findNearest(entityType2, resourceId1, pos5);
        REQUIRE(lock5 != nullptr);
        REQUIRE(lock5->getEntity() == entity1);
        REQUIRE(lock5->getResourceType() == resourceId1);
        REQUIRE(lock5->isValid());
        REQUIRE(region->getPos(lock5->getEntity()) == pos1);

        lock2->release();
        REQUIRE(lock2->getEntity() == nullptr);
        REQUIRE(lock2->getResourceType() == nullptr);
        REQUIRE_FALSE(lock2->isValid());

        lock2 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock2 != nullptr);
        REQUIRE(lock2->getEntity() == entity1);
        REQUIRE(lock2->getResourceType() == resourceId1);
        REQUIRE(lock2->isValid());
        REQUIRE(region->getPos(lock2->getEntity()) == pos1);

        resourceManager->remove(entity1);
        REQUIRE(lock2->getEntity() == nullptr);
        REQUIRE(lock2->getResourceType() == nullptr);
        REQUIRE_FALSE(lock2->isValid());
        REQUIRE(lock5->getEntity() == nullptr);
        REQUIRE(lock5->getResourceType() == nullptr);
        REQUIRE_FALSE(lock5->isValid());

        lock2 = resourceManager->findNearest(entityType1, resourceId1, pos5);
        REQUIRE(lock2 == nullptr);

        frts::ResourceLockPtr lock6 = resourceManager->findNearest(entityType1, resourceId2, pos5);
        REQUIRE(lock6 != nullptr);
        REQUIRE(lock6->getEntity() == entity2);
        REQUIRE(lock6->getResourceType() == resourceId2);
        REQUIRE(lock6->isValid());
        REQUIRE(region->getPos(lock5->getEntity()) == pos1);
    }
    */
}
