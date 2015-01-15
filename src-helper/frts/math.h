#ifndef FRTS_MATH_H
#define FRTS_MATH_H

namespace frts
{
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
