#ifndef FRTS_POINT_H
#define FRTS_POINT_H

#include <cassert>
#include <functional>
#include <memory>
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
    inline PointPtr operator+(PointPtr lhs, PointPtr rhs)
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
    inline PointPtr operator-(PointPtr lhs, PointPtr rhs)
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
    inline PointPtr operator*(PointPtr lhs, PointPtr rhs)
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
    inline PointPtr operator*(PointPtr point, Point::value scalar)
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
    inline PointPtr operator*(Point::value scalar, PointPtr point)
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
    inline bool operator==(PointPtr lhs, PointPtr rhs)
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
    inline bool operator!=(PointPtr lhs, PointPtr rhs)
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Hash function object for points.
     */
    struct PointHash
    {
        std::hash<int>::result_type operator() (PointPtr point) const
        {
            if (point == nullptr)
            {
                return 0;
            }

            // The following represents the performance order of these hash algorithms.
            // The higher the better. Order was determined by comparing the timings
            // of execution of ModelStartup with a total of 16 z-levels precalculated.

            // See "Effective Java 2nd Edition" page 49
            // Result: ~5.5s
            int result = 17;
            result = 31 * result + point->getX();
            result = 31 * result + point->getY();
            result = 31 * result + point->getZ();
            return intHash(result);

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

    private:
        std::hash<int> intHash;
//        std::hash<std::string> stringHash;
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

    /**
     * @brief Less to function object for points.
     */
    struct PointLess
    {
        bool operator() (PointPtr lhs, PointPtr rhs) const
        {
            assert(lhs != nullptr);
            assert(rhs != nullptr);

            return lhs->getX() < rhs->getX() ||
                   lhs->getY() < rhs->getY() ||
                   lhs->getZ() < rhs->getZ();
        }
    };

    /**
     * @brief Unordered set of points.
     */
    using PointUnorderedSet = std::unordered_set<PointPtr, PointHash, PointEqual>;

    /**
     * @brief Vector of points.
     */
    using PointVector = std::vector<PointPtr>;
}

#endif // FRTS_POINT_H
