#include "EuclideanDistance.h"


frts::EuclideanDistance::EuclideanDistance()
{
}

frts::Point::length frts::EuclideanDistance::distance(PointPtr point1, PointPtr point2)
{
    assert(point1 != nullptr);
    assert(point2 != nullptr);

    return (point1 - point2)->getLength();
}
