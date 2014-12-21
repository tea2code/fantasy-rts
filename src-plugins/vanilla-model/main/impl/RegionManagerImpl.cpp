#include "RegionManagerImpl.h"

#include <main/ModelIds.h>


frts::RegionManagerImpl::RegionManagerImpl(RegionPtr region,
                                           LockableResourceManagerPtr resourceManager,
                                           LockableResourceManagerPtr resourceEntityManager,
                                           IdPtr hasResourceType, IdPtr isResourceType)
    : hasResourceType{hasResourceType}, isResourceType{isResourceType}, region{region},
      resourceManager{resourceManager}, resourceEntityManager{resourceEntityManager}
{
}

void frts::RegionManagerImpl::addChangedPos(PointPtr pos)
{
    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    addChangedPosLockFree(pos);
}

void frts::RegionManagerImpl::addChangedPosLockFree(PointPtr pos)
{
    if (pos != nullptr)
    {
        changedPos.insert(pos);
    }
}

std::vector<frts::PointPtr> frts::RegionManagerImpl::findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy, bool sameZLevel, SharedManagerPtr shared)
{
    assert(pos != nullptr);
    assert(blockedBy != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    return region->findFreeNeighbors(pos, blockedBy, sameZLevel, shared);
}

frts::PointPtr frts::RegionManagerImpl::findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy, SharedManagerPtr shared)
{
    assert(blockedBy != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    return region->findFreeRandomPos(zLevels, blockedBy, shared);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    return resourceManager->findNearest(entityGroup, resourceType, pos, shared);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    return resourceEntityManager->findNearest(entityGroup, resourceType, pos, shared);
}

frts::BlockPtr frts::RegionManagerImpl::getBlock(PointPtr pos, SharedManagerPtr shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    return region->getBlock(pos, shared);
}

frts::PointUnorderedSet frts::RegionManagerImpl::getChangedPos()
{
    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    return changedPos;
}

std::string frts::RegionManagerImpl::getName() const
{
    return ModelIds::regionManager();
}

std::vector<frts::PointPtr> frts::RegionManagerImpl::getNeightbors(PointPtr pos, bool sameZLevel, SharedManagerPtr shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    return region->getNeightbors(pos, sameZLevel, shared);
}

frts::PointPtr frts::RegionManagerImpl::getPos(EntityPtr entity, SharedManagerPtr shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    return region->getPos(entity, shared);
}

std::string frts::RegionManagerImpl::getTypeName() const
{
    return getName();
}

int frts::RegionManagerImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::RegionManagerImpl::getVersion() const
{
    return 1;
}

frts::PointPtr frts::RegionManagerImpl::removeEntity(EntityPtr entity, SharedManagerPtr shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    auto pos = region->removeEntity(entity, shared);
    resourceEntityManager->remove(entity);
    resourceManager->remove(entity);
    addChangedPosLockFree(pos);
    return pos;
}

void frts::RegionManagerImpl::resetChangedPos()
{
    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    changedPos.clear();
}

frts::PointPtr frts::RegionManagerImpl::setPos(EntityPtr entity, PointPtr pos, SharedManagerPtr shared)
{
    assert(entity != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    auto oldPos = region->setPos(entity, pos, shared);
    updateResourcesLockFree(entity, shared);
    addChangedPosLockFree(oldPos);
    addChangedPosLockFree(pos);
    return oldPos;
}

void frts::RegionManagerImpl::updateResources(EntityPtr entity, SharedManagerPtr shared)
{
    assert(entity != nullptr);

    std::lock_guard<std::recursive_mutex> lock(lockAllMutex);

    updateResourcesLockFree(entity, shared);
}

void frts::RegionManagerImpl::updateResourcesLockFree(EntityPtr entity, SharedManagerPtr)
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
