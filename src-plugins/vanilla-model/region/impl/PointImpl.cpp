#include "PointImpl.h"


frts::PointImpl::PointImpl(value x, value y, value z)
{
}

frts::Point::length frts::PointImpl::getLength() const
{
    return 0;
}

frts::Point::value frts::PointImpl::getX() const
{
    return 0;
}

frts::Point::value frts::PointImpl::getY() const
{
    return 0;
}

frts::Point::value frts::PointImpl::getZ() const
{
    return 0;
}

frts::PointPtr frts::PointImpl::operator+(const Point& other) const
{
    return nullptr;
}

frts::PointPtr frts::PointImpl::operator+=(const Point& other) const
{
    return nullptr;
}

frts::PointPtr frts::PointImpl::operator-(const Point& other) const
{
    return nullptr;
}

frts::PointPtr frts::PointImpl::operator-=(const Point& other) const
{
    return nullptr;
}

frts::PointPtr frts::PointImpl::operator*(const Point& other) const
{
    return nullptr;
}

frts::PointPtr frts::PointImpl::operator*=(const Point& other) const
{
    return nullptr;
}

frts::PointPtr frts::PointImpl::operator*(value scalar) const
{
    return nullptr;
}

frts::PointPtr frts::PointImpl::operator*=(value scalar) const
{
    return nullptr;
}

bool frts::PointImpl::operator==(const Point& other) const
{
    return getX() == other.getX() &&
           getY() == other.getY() &&
           getZ() == other.getZ();
}

bool frts::PointImpl::operator!=(const Point& other) const
{
    return !(*this == other);
}
