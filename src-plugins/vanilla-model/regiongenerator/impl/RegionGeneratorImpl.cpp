#include "RegionGeneratorImpl.h"

#include <region/impl/BlockImpl.h>
#include <region/impl/PointImpl.h>


frts::RegionGeneratorImpl::RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType,
                                               Point::value mapSizeX, Point::value mapSizeY)
    : blockingType{blockingType}, mapSizeX{mapSizeX}, mapSizeY{mapSizeY}, sortOrderType{sortOrderType}
{
}

frts::WriteableBlockPtr frts::RegionGeneratorImpl::newBlock(PointPtr, SharedManagerPtr)
{
    return makeBlock(blockingType, sortOrderType);
}
