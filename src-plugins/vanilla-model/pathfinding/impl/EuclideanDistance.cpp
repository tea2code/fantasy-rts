#include "EuclideanDistance.h"


frts::EuclideanDistance::EuclideanDistance()
{
}

frts::Point::length frts::EuclideanDistance::distance(PointPtr point1, PointPtr point2)
{
    return (point1 - point2)->getLength();
}
