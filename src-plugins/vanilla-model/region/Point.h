#ifndef FRTS_POINT_H
#define FRTS_POINT_H

#include <cassert>
#include <functional>
#include <memory>
#include <set>
#include <unordered_set>
#include <vector>


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
         * @brief Calculate hash of point.
         * @return The hash.
         */
        virtual std::size_t hash() = 0;

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
     * @param lhs First point.
     * @param rhs Second point.
     * @return Resulting point.
     */
    inline PointPtr operator+(const PointPtr& lhs, const PointPtr& rhs)
    {
        assert(lhs != nullptr);
        assert(rhs != nullptr);

        return *lhs + *rhs;
    }

    /**
     * @brief Substract two points.
     * @param lhs First point.
     * @param rhs Second point.
     * @return Resulting point.
     */
    inline PointPtr operator-(const PointPtr& lhs, const PointPtr& rhs)
    {
        assert(lhs != nullptr);
        assert(rhs != nullptr);

        return *lhs - *rhs;
    }

    /**
     * @brief Cross product of two points.
     * @param lhs First point.
     * @param rhs Second point.
     * @return Resulting point.
     */
    inline PointPtr operator*(const PointPtr& lhs, const PointPtr& rhs)
    {
        assert(lhs != nullptr);
        assert(rhs != nullptr);

        return *lhs * *rhs;
    }

    /**
     * @brief Scalar multiplication.
     * @param lhs First point.
     * @param rhs Second point.
     * @return Resulting point.
     */
    inline PointPtr operator*(const PointPtr& point, Point::value scalar)
    {
        assert(point != nullptr);

        return *point * scalar;
    }

    /**
     * @brief Scalar multiplication with scalar lhs.
     * @param lhs First point.
     * @param rhs Second point.
     * @return Resulting point.
     */
    inline PointPtr operator*(Point::value scalar, const PointPtr& point)
    {
        assert(point != nullptr);

        return *point * scalar;
    }

    /**
     * @brief Compare equality.
     * @param lhs First point.
     * @param rhs Second point.
     * @return True if points are equal.
     */
    inline bool operator==(const PointPtr& lhs, const PointPtr& rhs)
    {
        bool lhsNull = (lhs == nullptr);
        bool rhsNull = (rhs == nullptr);
        return (lhsNull && rhsNull) || (!lhsNull && !rhsNull && *lhs == *rhs);
    }

    /**
     * @brief Compare inequality.
     * @param lhs First point.
     * @param rhs Second point.
     * @return True if points are not equal.
     */
    inline bool operator!=(const PointPtr& lhs, const PointPtr& rhs)
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Compare less.
     * @param lhs First point.
     * @param rhs Second point.
     * @return True if lhs is less than rhs.
     */
    inline bool operator<(const PointPtr& lhs, const PointPtr& rhs)
    {
        assert(lhs != nullptr);
        assert(rhs != nullptr);

        return lhs->getX() < rhs->getX() ||
               lhs->getY() < rhs->getY() ||
               lhs->getZ() < rhs->getZ();
    }
}

namespace std
{
    /**
     * @brief Hash for points.
     */
    template <>
    struct hash<frts::PointPtr>
    {
        size_t operator()(const frts::PointPtr& point) const
        {
            if (point == nullptr)
            {
                return 0;
            }

            return point->hash();
        }
    };
}

namespace frts
{
    /**
     * @brief Set of points.
     */
    using PointSet = std::set<PointPtr>;

    /**
     * @brief Unordered set of points.
     */
    using PointUnorderedSet = std::unordered_set<PointPtr>;

    /**
     * @brief Vector of points.
     */
    using PointVector = std::vector<PointPtr>;
}

#endif // FRTS_POINT_H
