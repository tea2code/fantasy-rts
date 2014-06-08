#include "RegionConfigImpl.h"


frts::RegionConfigImpl::RegionConfigImpl()
{
}

std::string frts::RegionConfigImpl::getName() const
{
    return "frts::RegionConfig";
}

frts::Point::value frts::RegionConfigImpl::getMapSizeX() const
{
    return sizeX;
}

frts::Point::value frts::RegionConfigImpl::getMapSizeY() const
{
    return sizeY;
}

void frts::RegionConfigImpl::setMapSizeX(Point::value size)
{
    sizeX = size;
}

void frts::RegionConfigImpl::setMapSizeY(Point::value size)
{
    sizeY = size;
}
