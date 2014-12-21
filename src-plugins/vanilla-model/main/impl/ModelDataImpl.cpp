#include "ModelDataImpl.h"

#include <main/ModelIds.h>


frts::ModelDataImpl::ModelDataImpl()
{
}

std::string frts::ModelDataImpl::getName() const
{
    return ModelIds::modelData();
}

frts::Point::value frts::ModelDataImpl::getMapSizeX() const
{
    return sizeX;
}

frts::Point::value frts::ModelDataImpl::getMapSizeY() const
{
    return sizeY;
}

unsigned int frts::ModelDataImpl::getPrecalculateDown() const
{
    return precalculateDown;
}

unsigned int frts::ModelDataImpl::getPrecalculateUp() const
{
    return precalculateUp;
}

frts::Point::value frts::ModelDataImpl::getSurfaceZLevel() const
{
    return surfaceZLevel;
}

std::string frts::ModelDataImpl::getTypeName() const
{
    return getName();
}

int frts::ModelDataImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::ModelDataImpl::getVersion() const
{
    return 2;
}

void frts::ModelDataImpl::setMapSizeX(Point::value size)
{
    sizeX = size;
}

void frts::ModelDataImpl::setMapSizeY(Point::value size)
{
    sizeY = size;
}

void frts::ModelDataImpl::setPrecalculateDown(unsigned int zLevels)
{
    precalculateDown = zLevels;
}

void frts::ModelDataImpl::setPrecalculateUp(unsigned int zLevels)
{
    precalculateUp = zLevels;
}

void frts::ModelDataImpl::setSurfaceZLevel(Point::value zLevel)
{
    surfaceZLevel = zLevel;
}
