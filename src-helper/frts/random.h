#ifndef FRTS_RANDOM_H
#define FRTS_RANDOM_H

#include  <random>
#include  <iterator>


/**
 * @brief Select randomly from given range.
 * @see http://stackoverflow.com/a/16421677
 * @param start Begin of range.
 * @param end End of range.
 * @param generator The random generator.
 * @return The selected random value.
 */
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& generator)
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
Iter select_randomly(Iter start, Iter end)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

#endif // FRTS_RANDOM_H
