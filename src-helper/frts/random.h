#ifndef FRTS_RANDOM_H
#define FRTS_RANDOM_H

#include  <random>
#include  <iterator>


namespace frts
{
    /**
     * @brief Generate a random floating point number in interval [start, end].
     * @param start Start of interval.
     * @param end End of interval.
     * @return A random floating point number.
     */
    template<typename FloatType>
    FloatType randomFloat(FloatType start, FloatType end)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(start, end);
        return dist(gen);
    }

    /**
     * @brief Generate a random integer number in interval [start, end].
     * @param start Start of interval.
     * @param end End of interval.
     * @return A random integer.
     */
    template<typename IntegerType>
    IntegerType randomInteger(IntegerType start, IntegerType end)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(start, end);
        return dist(gen);
    }

    /**
     * @brief Select randomly from given range.
     * @see http://stackoverflow.com/a/16421677
     * @param start Begin of range.
     * @param end End of range.
     * @param generator The random generator.
     * @return The selected random value.
     */
    template<typename Iter, typename RandomGenerator>
    Iter selectRandomly(Iter start, Iter end, RandomGenerator& generator)
    {
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(generator));
        return start;
    }

    /**
     * @brief Select randomly from given range.
     * @see http://stackoverflow.com/a/16421677
     * @param start Begin of range.
     * @param end End of range.
     * @return The selected random value.
     */
    template<typename Iter>
    Iter selectRandomly(Iter start, Iter end)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return selectRandomly(start, end, gen);
    }
}

#endif // FRTS_RANDOM_H
