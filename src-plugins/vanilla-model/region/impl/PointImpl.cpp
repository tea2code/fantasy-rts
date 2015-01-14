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

std::size_t frts::PointImpl::hash()
{
    // The following represents the performance order of these hash algorithms.
    // The higher the better. Order was determined by comparing the timings
    // of execution of ModelStartup with a total of 16 z-levels precalculated.

    // See "Effective Java 2nd Edition" page 49
    // Result: ~5.5s
        size_t result = 17;
        result = 31 * result + x;
        result = 31 * result + y;
        result = 31 * result + z;
        return std::hash<std::size_t>()(result);

    // See http://stackoverflow.com/a/5929567/1931663 ("mod n" removed because the unordered_map does this as far as i know).
    // Result: ~5.5s
//            return intHash(point->getX() * 73856093 ^ point->getY() *  19349663 ^ point->getZ() * 83492791);

    // See http://stackoverflow.com/a/2634715/1931663
    // Result: ~7s
//            return intHash(51 + point->getX() * 51 + point->getY() * 51 + point->getZ());

    // String hashing
    // Result: ~9s
//            return stringHash(std::to_string(point->getX()) + " " + std::to_string(point->getY()) + " " + std::to_string(point->getZ()));

    // See http://stackoverflow.com/a/16794345/1931663
    // Result: ~10-11s
//            size_t h1 = intHash(point->getX());
//            size_t h2 = intHash(point->getY());
//            size_t h3 = intHash(point->getZ());
//            return (h1 ^ (h2 << 1)) ^ h3;

    // Original naive variant.
    // Result: ~26s
//            return intHash(point->getX() + point->getY() + point->getZ());

    // Maybe...
    // Result: Nope, stopped execution because it took to long.
//            return intHash(point->getX() * point->getY() * point->getZ());
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
