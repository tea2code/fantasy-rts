#include "ModelDataImpl.h"

#include <main/ModelIds.h>


frts::ModelDataImpl::ModelDataImpl()
{
}

frts::DistanceAlgorithmPtr frts::ModelDataImpl::getDistanceAlgorithm() const
{
    return distanceAlgorithm;
}

frts::IdPtr frts::ModelDataImpl::getHasResourceType() const
{
    return hasResourceType;
}

frts::IdPtr frts::ModelDataImpl::getIsResourceType() const
{
    return isResourceType;
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

void frts::ModelDataImpl::setDistanceAlgorithm(DistanceAlgorithmPtr distanceAlgorithm)
{
    this->distanceAlgorithm = distanceAlgorithm;
}

void frts::ModelDataImpl::setHasResourceType(IdPtr hasResourceType)
{
    this->hasResourceType = hasResourceType;
}

void frts::ModelDataImpl::setIsResourceType(IdPtr isResourceType)
{
    this->isResourceType = isResourceType;
}

void frts::ModelDataImpl::setMapSizeX(Point::value size)
{
    sizeX = size;
}

void frts::ModelDataImpl::setMapSizeY(Point::value size)
{
    sizeY = size;
}
