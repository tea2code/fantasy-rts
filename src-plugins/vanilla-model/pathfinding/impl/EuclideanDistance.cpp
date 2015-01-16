#include "EuclideanDistance.h"


frts::EuclideanDistance::EuclideanDistance()
{
}

frts::Point::length frts::EuclideanDistance::distance(const PointPtr& point1, const PointPtr& point2)
{
    assert(point1 != nullptr);
    assert(point2 != nullptr);

    return (point1 - point2)->getLength();
}
