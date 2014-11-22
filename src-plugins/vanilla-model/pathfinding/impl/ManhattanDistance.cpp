#include "ManhattanDistance.h"

#include <math.h>


frts::ManhattanDistance::ManhattanDistance(double scale)
    : scale{scale}
{
}

frts::Point::length frts::ManhattanDistance::distance(PointPtr point1, PointPtr point2)
{
    double dx = std::abs(point1->getX() - point2->getX());
    double dy = std::abs(point1->getY() - point2->getY());
    double dz = std::abs(point1->getZ() - point2->getZ());
    return scale * (dx + dy + dz);
}
