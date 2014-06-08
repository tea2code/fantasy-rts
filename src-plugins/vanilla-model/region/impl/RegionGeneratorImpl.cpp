#include "RegionGeneratorImpl.h"

#include "BlockImpl.h"
#include "PointImpl.h"


frts::RegionGeneratorImpl::RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType,
                                               Point::value mapSizeX, Point::value mapSizeY)
    : blockingType{blockingType}, mapSizeX{mapSizeX},
      mapSizeY{mapSizeY}, sortOrderType{sortOrderType}
{
}

std::map<frts::PointPtr, frts::WriteableBlockPtr> frts::RegionGeneratorImpl::allBlocks(Point::value zLevel)
{
    std::map<PointPtr, WriteableBlockPtr> result;
    for (Point::value x = 0; x < mapSizeX; ++x)
    {
        for (Point::value y = 0; y < mapSizeY; ++y)
        {
            PointPtr pos = makePoint(x, y, zLevel);
            result[pos] = newBlock(pos);
        }
    }
    return result;
}

frts::WriteableBlockPtr frts::RegionGeneratorImpl::newBlock(PointPtr)
{
    return makeBlock(blockingType, sortOrderType);
}
