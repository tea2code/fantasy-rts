#include "RegionImpl.h"

#include <region/impl/PointImpl.h>

#include <frts/random.h>

#include <algorithm>


frts::RegionImpl::RegionImpl(Point::value mapSizeX, Point::value mapSizeY,
                             RegionGeneratorPtr regionGenerator)
    : mapSizeX{mapSizeX}, mapSizeY{mapSizeY}, regionGenerator{regionGenerator}
{
}

std::vector<frts::PointPtr> frts::RegionImpl::findFreeNeighbors(PointPtr pos, BlockedByPtr blockedBy, bool sameZLevel, SharedManagerPtr shared)
{
    auto result = getNeightbors(pos, sameZLevel, shared);

    // Because erase() returns an iterator to the next element the following
    // loop is possible. Only important detail is to increment it inside the
    // else case and not in the loop header.
    // See http://stackoverflow.com/a/8628963/1931663
    for (auto it = result.begin(); it != result.end();)
    {
        auto block = getWriteableBlock(*it, shared);
        if(block->isBlocking(blockedBy))
        {
            it = result.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return result;
}

frts::PointPtr frts::RegionImpl::findFreeRandomPos(const std::vector<Point::value>& zLevels, BlockedByPtr blockedBy, SharedManagerPtr shared)
{
    // Let's try at least 100 times. Still might not find a free position.
    const int numTries = std::min(mapSizeX * mapSizeY * static_cast<Point::value>(zLevels.size()), 100);

    PointPtr result = nullptr;

    for (int i = 0; i < numTries; ++i)
    {
        Point::value x = frts::randomInteger<Point::value>(0, mapSizeX - 1);
        Point::value y = frts::randomInteger<Point::value>(0, mapSizeY - 1);
        Point::value z = *frts::selectRandomly(zLevels.begin(), zLevels.end());

        result = makePoint(x, y, z);
        if (!getWriteableBlock(result, shared)->isBlocking(blockedBy))
        {
            break;
        }
        else
        {
            result = nullptr;
        }
    }
    
    return nullptr;
}

frts::BlockPtr frts::RegionImpl::getBlock(PointPtr pos, SharedManagerPtr shared)
{
    return getWriteableBlock(pos, shared);
}

std::vector<frts::PointPtr> frts::RegionImpl::getNeightbors(PointPtr pos, bool sameZLevel, SharedManagerPtr)
{
    int x = pos->getX();
    int y = pos->getY();
    int z = pos->getZ();

    std::vector<PointPtr> result;

    // North
    if (y - 1 >= 0)
    {
        result.push_back(makePoint(x, y - 1, z));
    }

    // East
    if (x + 1 < mapSizeX)
    {
        result.push_back(makePoint(x + 1, y, z));
    }

    // South
    if (y + 1 < mapSizeY)
    {
        result.push_back(makePoint(x, y + 1, z));
    }

    // West
    if (x - 1 >= 0)
    {
        result.push_back(makePoint(x - 1, y, z));
    }

    if (!sameZLevel)
    {
        // Up
        result.push_back(makePoint(x, y, z + 1));

        // Down
        result.push_back(makePoint(x, y, z - 1));
    }

    return result;
}

frts::PointPtr frts::RegionImpl::getPos(EntityPtr entity, SharedManagerPtr)
{
    auto found = entityPos.find(entity);
    if (found != entityPos.end())
    {
        return found->second;
    }
    else
    {
        return nullptr;
    }
}

frts::WriteableBlockPtr frts::RegionImpl::getWriteableBlock(PointPtr pos, SharedManagerPtr shared)
{
    frts::WriteableBlockPtr result = nullptr;
    auto it = posBlock.find(pos);
    if (it != posBlock.end())
    {
        result = it->second;
    }
    else
    {
        result = regionGenerator->newBlock(pos, shared);
        for (auto entity : result->getEntities())
        {
            entityPos[entity] = pos;
        }
        posBlock[pos] = result;
    }
    return result;
}

frts::PointPtr frts::RegionImpl::removeEntity(EntityPtr entity, SharedManagerPtr shared)
{
    auto pos = getPos(entity, shared);
    if (pos != nullptr)
    {
        // Remove from block.
        getWriteableBlock(pos, shared)->remove(entity);

        // Remove from entity pos map.
        entityPos.erase(entity);
    }
    return pos;
}

frts::PointPtr frts::RegionImpl::setPos(EntityPtr entity, PointPtr pos, SharedManagerPtr shared)
{
    // Remove from block if exists.
    auto lastPos = removeEntity(entity, shared);

    // Insert in block.
    getWriteableBlock(pos, shared)->insert(entity);

    // Insert in entity pos map.
    entityPos[entity] = pos;

    return lastPos;
}
