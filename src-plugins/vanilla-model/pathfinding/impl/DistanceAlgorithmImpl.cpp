#include "DistanceAlgorithmImpl.h"


frts::DistanceAlgorithmImpl::DistanceAlgorithmImpl()
{
}

frts::Point::length frts::DistanceAlgorithmImpl::distance(PointPtr point1, PointPtr point2)
{
    return (point1 - point2)->getLength();
}
