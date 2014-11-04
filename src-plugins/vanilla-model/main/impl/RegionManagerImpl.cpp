#include "RegionManagerImpl.h"


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
    changedPos.insert(pos);
}

std::vector<frts::PointPtr> frts::RegionManagerImpl::findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy, SharedManagerPtr shared)
{
    return region->findFreeNeighbors(pos, blockedBy, shared);
}

frts::PointPtr frts::RegionManagerImpl::findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy, SharedManagerPtr shared)
{
    return region->findFreeRandomPos(zLevels, blockedBy, shared);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared)
{
    return resourceManager->findNearest(entityGroup, resourceType, pos, shared);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos, SharedManagerPtr shared)
{
    return resourceEntityManager->findNearest(entityGroup, resourceType, pos, shared);
}

frts::BlockPtr frts::RegionManagerImpl::getBlock(PointPtr pos, SharedManagerPtr shared)
{
    return region->getBlock(pos, shared);
}

frts::RegionManager::PointSet frts::RegionManagerImpl::getChangedPos()
{
    return changedPos;
}

std::string frts::RegionManagerImpl::getName() const
{
    return "frts::RegionManager";
}

std::vector<frts::PointPtr> frts::RegionManagerImpl::getNeightbors(PointPtr pos, SharedManagerPtr shared)
{
    return region->getNeightbors(pos, shared);
}

frts::PointPtr frts::RegionManagerImpl::getPos(EntityPtr entity, SharedManagerPtr shared)
{
    return region->getPos(entity, shared);
}

void frts::RegionManagerImpl::removeEntity(EntityPtr entity, SharedManagerPtr shared)
{
    auto pos = region->removeEntity(entity, shared);
    resourceEntityManager->remove(entity);
    resourceManager->remove(entity);
    addChangedPos(pos);
}

void frts::RegionManagerImpl::resetChangedPos()
{
    changedPos.clear();
}

void frts::RegionManagerImpl::setPos(EntityPtr entity, PointPtr pos, SharedManagerPtr shared)
{
    region->setPos(entity, pos, shared);
    updateResources(entity, shared);
    addChangedPos(pos);
}

void frts::RegionManagerImpl::updateResources(EntityPtr entity, SharedManagerPtr)
{
    bool hasResourceSet = false;
    bool isResourceSet = false;
    for (auto component : entity->getComponents())
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
