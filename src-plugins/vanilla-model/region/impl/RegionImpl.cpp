#include "RegionImpl.h"


frts::RegionImpl::RegionImpl(RegionGeneratorPtr regionGenerator)
    : regionGenerator{regionGenerator}
{
}

std::vector<frts::PointPtr> frts::RegionImpl::findFreeNeighbors(PointPtr pos, BlockingPtr blockedBy)
{
    return {};
}

frts::PointPtr frts::RegionImpl::findFreeRandomPos(std::vector<Point::value> zLevels, BlockingPtr blockedBy)
{
    return nullptr;
}

frts::BlockPtr frts::RegionImpl::getBlock(PointPtr pos)
{
    return nullptr;
}

std::vector<frts::PointPtr> frts::RegionImpl::getNeightbors(PointPtr pos)
{
    return {};
}

frts::PointPtr frts::RegionImpl::getPos(EntityPtr entity)
{
    return nullptr;
}

void frts::RegionImpl::removeEntity(EntityPtr entity)
{

}

void frts::RegionImpl::setPos(EntityPtr entity, PointPtr pos)
{

}
