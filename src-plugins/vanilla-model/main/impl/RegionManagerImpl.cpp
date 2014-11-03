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

std::vector<frts::PointPtr> frts::RegionManagerImpl::findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy)
{
    return region->findFreeNeighbors(pos, blockedBy);
}

frts::PointPtr frts::RegionManagerImpl::findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy)
{
    return region->findFreeRandomPos(zLevels, blockedBy);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return resourceManager->findNearest(entityGroup, resourceType, pos);
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return resourceEntityManager->findNearest(entityGroup, resourceType, pos);
}

frts::BlockPtr frts::RegionManagerImpl::getBlock(PointPtr pos)
{
    return region->getBlock(pos);
}

frts::RegionManager::PointSet frts::RegionManagerImpl::getChangedPos()
{
    return changedPos;
}

std::string frts::RegionManagerImpl::getName() const
{
    return "frts::RegionManager";
}

std::vector<frts::PointPtr> frts::RegionManagerImpl::getNeightbors(PointPtr pos)
{
    return region->getNeightbors(pos);
}

frts::PointPtr frts::RegionManagerImpl::getPos(EntityPtr entity)
{
    return region->getPos(entity);
}

void frts::RegionManagerImpl::removeEntity(EntityPtr entity)
{
    auto pos = region->removeEntity(entity);
    resourceEntityManager->remove(entity);
    resourceManager->remove(entity);
    addChangedPos(pos);
}

void frts::RegionManagerImpl::resetChangedPos()
{
    changedPos.clear();
}

void frts::RegionManagerImpl::setPos(EntityPtr entity, PointPtr pos)
{
    region->setPos(entity, pos);
    updateResources(entity);
    addChangedPos(pos);
}

void frts::RegionManagerImpl::updateResources(EntityPtr entity)
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
