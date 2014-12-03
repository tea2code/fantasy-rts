#include "RegionGeneratorImpl.h"

#include <region/impl/BlockImpl.h>
#include <region/impl/PointImpl.h>


frts::RegionGeneratorImpl::RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType,
                                               Point::value mapSizeX, Point::value mapSizeY)
    : blockingType{blockingType}, mapSizeX{mapSizeX}, mapSizeY{mapSizeY}, sortOrderType{sortOrderType}
{
}

std::map<frts::PointPtr, frts::WriteableBlockPtr> frts::RegionGeneratorImpl::allBlocks(Point::value zLevel, SharedManagerPtr shared)
{
    std::map<PointPtr, WriteableBlockPtr> result;
    for (Point::value x = 0; x < mapSizeX; ++x)
    {
        for (Point::value y = 0; y < mapSizeY; ++y)
        {
            auto pos = makePoint(x, y, zLevel);
            result[pos] = newBlock(pos, shared);
        }
    }
    return result;
}

frts::WriteableBlockPtr frts::RegionGeneratorImpl::newBlock(PointPtr, SharedManagerPtr)
{
    return makeBlock(blockingType, sortOrderType);
}
