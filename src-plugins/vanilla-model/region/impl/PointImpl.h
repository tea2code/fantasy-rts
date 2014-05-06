#ifndef FRTS_POINTIMPL_H
#define FRTS_POINTIMPL_H

#include <region/Point.h>


namespace frts
{
    class PointImpl : public Point
    {
    public:
        PointImpl(value x, value y, value z);

        length getLength() const override;
        value getX() const override;
        value getY() const override;
        value getZ() const override;
        PointPtr operator+(const Point& other) const override;
        PointPtr operator+=(const Point& other) const override;
        PointPtr operator-(const Point& other) const override;
        PointPtr operator-=(const Point& other) const override;
        PointPtr operator*(const Point& other) const override;
        PointPtr operator*=(const Point& other) const override;
        PointPtr operator*(value scalar) const;
        PointPtr operator*=(value scalar) const;
        bool operator==(const Point& other) const override;
        bool operator!=(const Point& other) const override;
    };
}

#endif // FRTS_POINTIMPL_H
