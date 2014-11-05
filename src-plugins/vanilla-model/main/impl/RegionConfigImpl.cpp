#include "RegionConfigImpl.h"

#include <main/ModelIds.h>


frts::RegionConfigImpl::RegionConfigImpl()
{
}

std::string frts::RegionConfigImpl::getName() const
{
    return ModelIds::regionConfig();
}

frts::Point::value frts::RegionConfigImpl::getMapSizeX() const
{
    return sizeX;
}

frts::Point::value frts::RegionConfigImpl::getMapSizeY() const
{
    return sizeY;
}

std::string frts::RegionConfigImpl::getTypeName() const
{
    return getName();
}

int frts::RegionConfigImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::RegionConfigImpl::getVersion() const
{
    return 1;
}

void frts::RegionConfigImpl::setMapSizeX(Point::value size)
{
    sizeX = size;
}

void frts::RegionConfigImpl::setMapSizeY(Point::value size)
{
    sizeY = size;
}
