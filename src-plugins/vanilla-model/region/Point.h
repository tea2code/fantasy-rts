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
        using length = double;

        /**
         * @brief Type of single coordinate.
         */
        using value = int;

    public:
        virtual ~Point() {}

        /**
         * @brief The length of the point.
         * @return Length value.
         */
        virtual length getLength() const = 0;

        /**
         * @brief Get the x value.
         * @return The x value.
         */
        virtual value getX() const = 0;

        /**
         * @brief Get the y value.
         * @return The y value.
         */
        virtual value getY() const = 0;

        /**
         * @brief Get the z value.
         * @return The z value.
         */
        virtual value getZ() const = 0;

        /**
         * @brief Add two points.
         * @param other The second point.
         * @return Resulting point.
         */
        virtual PointPtr operator+(const Point& other) const = 0;

        /**
         * @brief Substract two points.
         * @param other The second point.
         * @return Resulting point.
         */
        virtual PointPtr operator-(const Point& other) const = 0;

        /**
         * @brief Cross product of two points.
         * @param other The second point.
         * @return Resulting point.
         */
        virtual PointPtr operator*(const Point& other) const = 0;

        /**
         * @brief Scalar multiplication.
         * @param scalar The scalar.
         * @return Resulting point pointer.
         */
        virtual PointPtr operator*(value scalar) const = 0;

        /**
         * @brief Compare equality.
         * @param other The second point.
         * @return True if points are equal.
         */
        virtual bool operator==(const Point& other) const = 0;

        /**
         * @brief Compare inequality.
         * @param other The second point.
         * @return True if points are not equal.
         */
        virtual bool operator!=(const Point& other) const = 0;
    };

    /**
     * @brief Scalar multiplication with scalar first.
     * @param scalar The scalar.
     * @param point The point.
     * @return Resulting point.
     */
    inline PointPtr operator*(Point::value scalar, const Point& point)
    {
        return point * scalar;
    }

    /**
     * @brief Add two points.
     * @param first First point.
     * @param second Second point.
     * @return Resulting point.
     */
    inline PointPtr operator+(PointPtr first, PointPtr second)
    {
        return *first + *second;
    }

    /**
     * @brief Substract two points.
     * @param first First point.
     * @param second Second point.
     * @return Resulting point.
     */
    inline PointPtr operator-(PointPtr first, PointPtr second)
    {
        return *first - *second;
    }

    /**
     * @brief Cross product of two points.
     * @param first First point.
     * @param second Second point.
     * @return Resulting point.
     */
    inline PointPtr operator*(PointPtr first, PointPtr second)
    {
        return *first * *second;
    }

    /**
     * @brief Scalar multiplication.
     * @param first First point.
     * @param second Second point.
     * @return Resulting point.
     */
    inline PointPtr operator*(PointPtr point, Point::value scalar)
    {
        return *point * scalar;
    }

    /**
     * @brief Scalar multiplication with scalar first.
     * @param first First point.
     * @param second Second point.
     * @return Resulting point.
     */
    inline PointPtr operator*(Point::value scalar, PointPtr point)
    {
        return *point * scalar;
    }

    /**
     * @brief Compare equality.
     * @param first First point.
     * @param second Second point.
     * @return True if points are equal.
     */
    inline bool operator==(PointPtr first, PointPtr second)
    {
        return *first == *second;
    }

    /**
     * @brief Compare inequality.
     * @param first First point.
     * @param second Second point.
     * @return True if points are not equal.
     */
    inline bool operator!=(PointPtr first, PointPtr second)
    {
        return *first != *second;
    }
}

#endif // FRTS_POINT_H
