#include "RegionImpl.h"


frts::RegionImpl::RegionImpl(Point::value mapSizeX, Point::value mapSizeY,
                             RegionGeneratorPtr regionGenerator)
    : mapSizeX{mapSizeX}, mapSizeY{mapSizeY}, regionGenerator{regionGenerator}
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
    return getWriteableBlock(pos);
}

std::vector<frts::PointPtr> frts::RegionImpl::getNeightbors(PointPtr pos)
{
    return {};
}

frts::PointPtr frts::RegionImpl::getPos(EntityPtr entity)
{
    return entityPos[entity];
}

frts::WriteableBlockPtr frts::RegionImpl::getWriteableBlock(PointPtr pos)
{
    frts::WriteableBlockPtr result = nullptr;
    auto it = posBlock.find(pos);
    if (it != posBlock.end())
    {
        result = it->second;
    }
    else
    {
        result = regionGenerator->newBlock(pos);
        posBlock[pos] = result;
    }
    return result;
}

void frts::RegionImpl::removeEntity(EntityPtr entity)
{
    PointPtr pos = getPos(entity);
    if (pos != nullptr)
    {
        // Remove from block.
        getWriteableBlock(pos)->remove(entity);

        // Remove from entity pos map.
        entityPos.erase(entity);
    }
}

void frts::RegionImpl::setPos(EntityPtr entity, PointPtr pos)
{
    // Remove from block if exists.
    removeEntity(entity);

    // Insert in block.
    getWriteableBlock(pos)->insert(entity);

    // Insert in entity pos map.
    entityPos[entity] = pos;
}
