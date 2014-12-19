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

    return region->findFreeNeighbors(pos, blockedBy, sameZLevel, shared);
}

frts::PointPtr frts::RegionManagerImpl::findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy, SharedManagerPtr shared)
{
    assert(blockedBy != nullptr);
    assert(shared != nullptr);

    return region->findFreeRandomPos(zLevels, blockedBy, shared);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    return resourceManager->findNearest(entityGroup, resourceType, pos, shared);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared)
{
    assert(entityGroup != nullptr);
    assert(resourceType != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    return resourceEntityManager->findNearest(entityGroup, resourceType, pos, shared);
}

frts::BlockPtr frts::RegionManagerImpl::getBlock(PointPtr pos, SharedManagerPtr shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    return region->getBlock(pos, shared);
}

frts::PointUnorderedSet frts::RegionManagerImpl::getChangedPos()
{
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

    return region->getNeightbors(pos, sameZLevel, shared);
}

frts::PointPtr frts::RegionManagerImpl::getPos(EntityPtr entity, SharedManagerPtr shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

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

    auto pos = region->removeEntity(entity, shared);
    resourceEntityManager->remove(entity);
    resourceManager->remove(entity);
    addChangedPos(pos);
    return pos;
}

void frts::RegionManagerImpl::resetChangedPos()
{
    changedPos.clear();
}

frts::PointPtr frts::RegionManagerImpl::setPos(EntityPtr entity, PointPtr pos, SharedManagerPtr shared)
{
    assert(entity != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    auto oldPos = region->setPos(entity, pos, shared);
    updateResources(entity, shared);
    addChangedPos(oldPos);
    addChangedPos(pos);
    return oldPos;
}

void frts::RegionManagerImpl::updateResources(EntityPtr entity, SharedManagerPtr)
{
    assert(entity != nullptr);

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
