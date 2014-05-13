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
         * @param other The rhs point.
         * @return Resulting point.
         */
        virtual PointPtr operator+(const Point& other) const = 0;

        /**
         * @brief Substract two points.
         * @param other The rhs point.
         * @return Resulting point.
         */
        virtual PointPtr operator-(const Point& other) const = 0;

        /**
         * @brief Cross product of two points.
         * @param other The rhs point.
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
         * @param other The rhs point.
         * @return True if points are equal.
         */
        virtual bool operator==(const Point& other) const = 0;

        /**
         * @brief Compare inequality.
         * @param other The rhs point.
         * @return True if points are not equal.
         */
        virtual bool operator!=(const Point& other) const = 0;
    };

    /**
     * @brief Scalar multiplication with scalar lhs.
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
     * @param lhs lhs point.
     * @param rhs rhs point.
     * @return Resulting point.
     */
    inline PointPtr operator+(PointPtr lhs, PointPtr rhs)
    {
        return *lhs + *rhs;
    }

    /**
     * @brief Substract two points.
     * @param lhs lhs point.
     * @param rhs rhs point.
     * @return Resulting point.
     */
    inline PointPtr operator-(PointPtr lhs, PointPtr rhs)
    {
        return *lhs - *rhs;
    }

    /**
     * @brief Cross product of two points.
     * @param lhs lhs point.
     * @param rhs rhs point.
     * @return Resulting point.
     */
    inline PointPtr operator*(PointPtr lhs, PointPtr rhs)
    {
        return *lhs * *rhs;
    }

    /**
     * @brief Scalar multiplication.
     * @param lhs lhs point.
     * @param rhs rhs point.
     * @return Resulting point.
     */
    inline PointPtr operator*(PointPtr point, Point::value scalar)
    {
        return *point * scalar;
    }

    /**
     * @brief Scalar multiplication with scalar lhs.
     * @param lhs lhs point.
     * @param rhs rhs point.
     * @return Resulting point.
     */
    inline PointPtr operator*(Point::value scalar, PointPtr point)
    {
        return *point * scalar;
    }

    /**
     * @brief Compare equality.
     * @param lhs lhs point.
     * @param rhs rhs point.
     * @return True if points are equal.
     */
    inline bool operator==(PointPtr lhs, PointPtr rhs)
    {
        return *lhs == *rhs;
    }

    /**
     * @brief Compare inequality.
     * @param lhs lhs point.
     * @param rhs rhs point.
     * @return True if points are not equal.
     */
    inline bool operator!=(PointPtr lhs, PointPtr rhs)
    {
        return *lhs != *rhs;
    }

    /**
     * @brief Hash function object for points.
     */
    struct PointHash
    {
        std::size_t operator() (PointPtr point) const
        {
            return intHash(point->getX() + point->getY() + point->getZ());
        }

    private:
        std::hash<int> intHash;
    };

    /**
     * @brief Equal to function object for points.
     */
    struct PointEqual
    {
        bool operator() (PointPtr lhs, PointPtr rhs) const
        {
            return lhs == rhs;
        }
    };
}

#endif // FRTS_POINT_H
