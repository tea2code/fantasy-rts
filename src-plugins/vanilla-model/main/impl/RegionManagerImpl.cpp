#include "RegionManagerImpl.h"


frts::RegionManagerImpl::RegionManagerImpl()
{
}

void frts::RegionManagerImpl::addChangedPos(PointPtr pos)
{

}

std::vector<frts::PointPtr> frts::RegionManagerImpl::findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy)
{
    return {};
}

frts::PointPtr frts::RegionManagerImpl::findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy)
{
    return nullptr;
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResource(IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return nullptr;
}

frts::ResourceLockPtr frts::RegionManagerImpl::findNearestResourceEntity(IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return nullptr;
}

frts::BlockPtr frts::RegionManagerImpl::getBlock(PointPtr pos)
{
    return nullptr;
}

std::unordered_set<frts::PointPtr> frts::RegionManagerImpl::getChangedPos()
{
    return {};
}


std::string frts::RegionManagerImpl::getName() const
{
    return "frts::RegionManager";
}

std::vector<frts::PointPtr> frts::RegionManagerImpl::getNeightbors(PointPtr pos)
{
    return {};
}

frts::PointPtr frts::RegionManagerImpl::getPos(EntityPtr entity)
{
    return nullptr;
}

void frts::RegionManagerImpl::removeEntity(EntityPtr entity)
{

}

void frts::RegionManagerImpl::resetChangedPos()
{

}

void frts::RegionManagerImpl::setPos(EntityPtr entity, PointPtr pos)
{

}
