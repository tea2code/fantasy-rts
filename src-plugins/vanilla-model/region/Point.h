#ifndef FRTS_POINT_H
#define FRTS_POINT_H

#include <memory>


namespace frts
{
    class Point;

    /**
     * @brief Pointer to Point.
     */
    using PointPtr = std::shared_ptr<Point>;

    /**
     * @brief Represents a coordinate in the region consisting of x, y and z.
     */
    class Point
    {
    public:
        /**
         * @brief Type of length.
         */
        using length = unsigned long;

        /**
         * @brief Type of single coordinate.
         */
        using value = int;

    public:
        virtual ~Point() {}

        virtual length getLength() const = 0;
        virtual value getX() const = 0;
        virtual value getY() const = 0;
        virtual value getZ() const = 0;
        virtual PointPtr operator+(const Point& other) const = 0;
        virtual PointPtr operator-(const Point& other) const = 0;
        virtual PointPtr operator*(const Point& other) const = 0;
        virtual PointPtr operator+=(const Point& other) const = 0;
        virtual PointPtr operator-=(const Point& other) const = 0;
        virtual PointPtr operator*=(const Point& other) const = 0;
        virtual bool operator==(const Point& other) const = 0;
        virtual bool operator!=(const Point& other) const = 0;
    };
}

#endif // FRTS_POINT_H
