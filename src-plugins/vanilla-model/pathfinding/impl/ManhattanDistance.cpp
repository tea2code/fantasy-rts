#include "ManhattanDistance.h"

#include <math.h>


frts::ManhattanDistance::ManhattanDistance(double scale)
    : scale{scale}
{
}

frts::Point::length frts::ManhattanDistance::distance(const PointPtr& point1, const PointPtr& point2)
{
    assert(point1 != nullptr);
    assert(point2 != nullptr);

    double dx = std::abs(point1->getX() - point2->getX());
    double dy = std::abs(point1->getY() - point2->getY());
    double dz = std::abs(point1->getZ() - point2->getZ());
    return scale * (dx + dy + dz);
}
