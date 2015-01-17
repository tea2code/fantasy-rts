#include "RegionImpl.h"

#include <region/impl/PointImpl.h>

#include <frts/random.h>

#include <algorithm>


frts::RegionImpl::RegionImpl(Point::value mapSizeX, Point::value mapSizeY,
                             const RegionGeneratorPtr& regionGenerator)
    : mapSizeX{mapSizeX}, mapSizeY{mapSizeY}, regionGenerator{regionGenerator}
{
#ifdef FAST_POS_BLOCK
    for (int z = 0; z <= std::abs(fastLookupHigh - fastLookupLow); ++z)
    {
        fastPosBlock.push_back(std::vector<std::vector<WriteableBlockPtr>>());
        fastPosBlock.at(z).reserve(mapSizeX);
        for (int x = 0; x < mapSizeX; ++x)
        {
            fastPosBlock.at(z).push_back(std::vector<WriteableBlockPtr>());
            fastPosBlock.at(z).at(x).reserve(mapSizeY);
            for (int y = 0; y < mapSizeY; ++y)
            {
                fastPosBlock.at(z).at(x).push_back(nullptr);
            }
        }
    }
#endif
}

std::vector<frts::PointPtr> frts::RegionImpl::findFreeNeighbors(const PointPtr& pos, const BlockedByPtr& blockedBy,
                                                                bool sameZLevel, const SharedManagerPtr& shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    auto result = getNeightbors(pos, sameZLevel, shared);

    if (blockedBy != nullptr)
    {
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
    }
    return result;
}

frts::PointPtr frts::RegionImpl::findFreeRandomPos(const std::vector<Point::value>& zLevels,
                                                   const BlockedByPtr& blockedBy,
                                                   const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

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
    
    return result;
}

frts::BlockPtr frts::RegionImpl::getBlock(const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    return getWriteableBlock(pos, shared);
}

std::vector<frts::PointPtr> frts::RegionImpl::getNeightbors(const PointPtr& pos, bool sameZLevel, const SharedManagerPtr&)
{
    assert(pos != nullptr);

    int x = pos->getX();
    int y = pos->getY();
    int z = pos->getZ();

    PointVector result;

    // North
    #pragma GCC diagnostic ignored "-Wstrict-overflow"
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
    #pragma GCC diagnostic ignored "-Wstrict-overflow"
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

frts::PointPtr frts::RegionImpl::getPos(const EntityPtr& entity, const SharedManagerPtr&)
{
    assert(entity != nullptr);

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

frts::WriteableBlockPtr frts::RegionImpl::getWriteableBlock(const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    frts::WriteableBlockPtr result = nullptr;

#ifdef FAST_POS_BLOCK
    bool useFastLookup = (fastLookupLow <= pos->getZ() && pos->getZ() <= fastLookupHigh);
    int fastZ = (pos->getZ() - fastLookupLow);
    if (useFastLookup)
    {
        // No bounds check for better performance.
        result = fastPosBlock[fastZ][pos->getX()][pos->getY()];
    }
    else
    {
#endif
        auto it = posBlock.find(pos);
        if (it != posBlock.end())
        {
            result = it->second;
        }
#ifdef FAST_POS_BLOCK
    }
#endif

    if (result == nullptr)
    {
        result = regionGenerator->newBlock(pos, shared);
        for (auto& entity : result->getEntities())
        {
            entityPos[entity] = pos;
        }
#ifdef FAST_POS_BLOCK
        if (useFastLookup)
        {
            fastPosBlock.at(fastZ).at(pos->getX()).at(pos->getY()) = result;
        }
        else
        {
#endif
            posBlock.insert(std::make_pair(pos, result));
#ifdef FAST_POS_BLOCK
        }
#endif
    }

    return result;
}

frts::PointPtr frts::RegionImpl::removeEntity(const EntityPtr& entity, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

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

frts::PointPtr frts::RegionImpl::setPos(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(pos != nullptr);
    assert(shared != nullptr);

    // Remove from block if exists.
    auto lastPos = removeEntity(entity, shared);

    // Insert in block.
    getWriteableBlock(pos, shared)->insert(entity);

    // Insert in entity pos map.
    entityPos[entity] = pos;

    return lastPos;
}
