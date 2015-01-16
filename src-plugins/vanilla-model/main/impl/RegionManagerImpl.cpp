#include "RegionManagerImpl.h"

#include <main/ModelData.h>
#include <main/ModelIds.h>
#include <main/ModelFactory.h>

#include <future>
#include <thread>


frts::RegionManagerImpl::RegionManagerImpl(const RegionPtr& region,
                                           const LockableResourceManagerPtr& resourceManager,
                                           const LockableResourceManagerPtr& resourceEntityManager,
                                           const IdPtr& hasResourceType, const IdPtr& isResourceType)
    : BaseDataValue(ModelIds::regionManager(), 2, ModelIds::regionManager(), 2),
      hasResourceType{hasResourceType}, isResourceType{isResourceType}, region{region},
      resourceManager{resourceManager}, resourceEntityManager{resourceEntityManager}
{
}

void frts::RegionManagerImpl::addChangedPos(const PointPtr& pos)
{
    std::lock_guard<RecursiveLock> lock(locker);

    addChangedPosLockFree(pos);
}

void frts::RegionManagerImpl::addChangedPosLockFree(const PointPtr& pos)
{
    if (pos != nullptr)
    {
        changedPos.insert(pos);
    }
}

std::vector<frts::PointPtr> frts::RegionManagerImpl::findFreeNeighbors(const PointPtr& pos, const BlockedByPtr& blockedBy,
                                                                       bool sameZLevel, const SharedManagerPtr& shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    return region->findFreeNeighbors(pos, blockedBy, sameZLevel, shared);
}

frts::PointPtr frts::RegionManagerImpl::findFreeRandomPos(const std::vector<Point::value>& zLevels,
                                                          const BlockedByPtr& blockedBy, const SharedManagerPtr& shared)
{
    assert(blockedBy != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    return region->findFreeRandomPos(zLevels, blockedBy, shared);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResource(const IdPtr& entityGroup, const IdPtr& resourceType,
                                                                   const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    return resourceManager->findNearest(entityGroup, resourceType, pos, shared);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResourceEntity(const IdPtr& entityGroup, const IdPtr& resourceType,
                                                                         const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    return resourceEntityManager->findNearest(entityGroup, resourceType, pos, shared);
}

frts::BlockPtr frts::RegionManagerImpl::getBlock(const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    // Seems to result in a dead lock. Further testing is necessary. Currently the block generation speed
    // is more than fast enough so we will leave it for now.
//    auto func = [](Point::value zLevel, Point::value sizeX, Point::value sizeY, SharedManagerPtr shared)
//    {
//        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
//        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
//        std::chrono::milliseconds sleepTime(1);
//        for (int x = 0; x < sizeX; ++x)
//        {
//            for (int y = 0; y < sizeY; ++y)
//            {
//                auto pos = mf->makePoint(x, y, zLevel);
//                rm->getBlock(pos, shared);
//                std::this_thread::sleep_for(sleepTime);
//            }
//        }
//    };

//    auto md = getDataValue<ModelData>(shared, ModelIds::modelData());
//    auto range = md->getPrecalculatedRange();
//    if (pos->getZ() < range.first + 3)
//    {
//        md->setPrecalculatedRange(std::make_pair(range.first - 1, range.second));
//        std::async(std::launch::async, func, range.first - 1, md->getMapSizeX(), md->getMapSizeY(), shared);
//    }
//    else if (range.second - 3 < pos->getZ())
//    {
//        md->setPrecalculatedRange(std::make_pair(range.first, range.second + 1));
//        std::async(std::launch::async, func, range.second + 1, md->getMapSizeX(), md->getMapSizeY(), shared);
//    }

    return region->getBlock(pos, shared);
}

frts::PointUnorderedSet frts::RegionManagerImpl::getChangedPos()
{
    std::lock_guard<RecursiveLock> lock(locker);

    return changedPos;
}

std::vector<frts::PointPtr> frts::RegionManagerImpl::getNeightbors(const PointPtr& pos, bool sameZLevel, const SharedManagerPtr& shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    // Doesn't need locking because it doesn't access any data.

    return region->getNeightbors(pos, sameZLevel, shared);
}

frts::PointPtr frts::RegionManagerImpl::getPos(const EntityPtr& entity, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    return region->getPos(entity, shared);
}

frts::PointPtr frts::RegionManagerImpl::removeEntity(const EntityPtr& entity, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    auto pos = region->removeEntity(entity, shared);
    resourceEntityManager->remove(entity);
    resourceManager->remove(entity);
    addChangedPosLockFree(pos);
    return pos;
}

void frts::RegionManagerImpl::resetChangedPos()
{
    std::lock_guard<RecursiveLock> lock(locker);

    changedPos.clear();
}

frts::PointPtr frts::RegionManagerImpl::setPos(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    auto oldPos = region->setPos(entity, pos, shared);
    updateResourcesLockFree(entity, shared);
    addChangedPosLockFree(oldPos);
    addChangedPosLockFree(pos);
    return oldPos;
}

void frts::RegionManagerImpl::updateResources(const EntityPtr& entity, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    updateResourcesLockFree(entity, shared);
}

void frts::RegionManagerImpl::updateResourcesLockFree(const EntityPtr& entity, const SharedManagerPtr&)
{
    bool hasResourceSet = false;
    bool isResourceSet = false;
    for (auto& component : entity->getComponents())
    {
        if (!hasResourceSet && component->getComponentType() == hasResourceType)
        {
            resourceEntityManager->add(entity);
            hasResourceSet = true;
        }
        else if (!isResourceSet && component->getComponentType() == isResourceType)
        {
            resourceManager->add(entity);
            isResourceSet = true;
        }
        if (hasResourceSet && isResourceSet)
        {
            break;
        }
    }
}
