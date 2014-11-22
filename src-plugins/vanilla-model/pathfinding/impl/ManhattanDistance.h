#ifndef FRTS_MANHATTANDISTANCE_H
#define FRTS_MANHATTANDISTANCE_H

#include <pathfinding/DistanceAlgorithm.h>


namespace frts
{
    /**
     * @brief Calculate distance using manhattan distance.
     */
    class ManhattanDistance : public DistanceAlgorithm
    {
    public:
        /**
         * @param scale Scale allows to tune the distance. For
         *        example A* may run faster (but less precise)
         *        using a higher scale value.
         */
        ManhattanDistance(double scale = 1.0);

        Point::length distance(PointPtr point1, PointPtr point2) override;

    private:
        double scale;
    };

    /**
     * @brief Create new distance algorithm based on manhattan distance.
     * @param scale Scale allows to tune the distance. For
     *        example A* may run faster (but less precise)
     *        using a higher scale value.
     * @return The distance algorithm.
     */
    inline DistanceAlgorithmPtr makeManhattanDistance(double scale = 1.0)
    {
        return std::make_shared<ManhattanDistance>(scale);
    }
}

#endif // FRTS_MANHATTANDISTANCE_H
