#include "PointImpl.h"

#include <cmath>


frts::PointImpl::PointImpl(value x, value y, value z)
    : x{x}, y{y}, z{z}
{
}

frts::Point::length frts::PointImpl::getLength() const
{
    return std::sqrt((x * x) + (y * y) + (z * z));
}

frts::Point::value frts::PointImpl::getX() const
{
    return x;
}

frts::Point::value frts::PointImpl::getY() const
{
    return y;
}

frts::Point::value frts::PointImpl::getZ() const
{
    return z;
}

frts::PointPtr frts::PointImpl::operator+(const Point& other) const
{
    return makePoint(x + other.getX(), y + other.getY(), z + other.getZ());
}

frts::PointPtr frts::PointImpl::operator-(const Point& other) const
{
    return makePoint(x - other.getX(), y - other.getY(), z - other.getZ());
}

frts::PointPtr frts::PointImpl::operator*(const Point& other) const
{
    value cx = y * other.getZ() - z * other.getY();
    value cy = z * other.getX() - x * other.getZ();
    value cz = x * other.getY() - y * other.getX();
    return makePoint(cx, cy, cz);
}

frts::PointPtr frts::PointImpl::operator*(value scalar) const
{
    return makePoint(x * scalar, y * scalar, z * scalar);
}

bool frts::PointImpl::operator==(const Point& other) const
{
    return x == other.getX() &&
           y == other.getY() &&
           z == other.getZ();
}

bool frts::PointImpl::operator!=(const Point& other) const
{
    return !(*this == other);
}
