#ifndef FRTS_MATH_H
#define FRTS_MATH_H

#include <cmath>
#include <limits>


namespace frts
{
    /**
     * @brief Equality comparison for floating point types.
     * @param lhs The first floating point.
     * @param rhs The second floating point.
     * @param epsilon The maximum difference to still count equal.
     * @return True if they can be considered equal else false.
     */
    template <typename FloatType>
    bool floatEqual(FloatType lhs, FloatType rhs, FloatType epsilon = std::numeric_limits<FloatType>::epsilon())
    {
        return std::fabs(lhs - rhs) < epsilon;
    }

    /**
     * @brief Rounds to the next integer.
     * @param value The floating point value.
     * @return The rounded integer.
     */
    template <typename IntegerType, typename FloatType>
    inline IntegerType round(FloatType value)
    {
        return static_cast<IntegerType>(value + 0.5);
    }
}

#endif // FRTS_MATH_H
