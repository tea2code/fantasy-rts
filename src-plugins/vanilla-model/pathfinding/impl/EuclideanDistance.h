#ifndef FRTS_EUCLIDEANDISTANCE_H
#define FRTS_EUCLIDEANDISTANCE_H

#include <pathfinding/DistanceAlgorithm.h>


namespace frts
{
    /**
     * @brief Calculate distance using euclidean distance.
     */
    class EuclideanDistance : public DistanceAlgorithm
    {
    public:
        EuclideanDistance();

        Point::length distance(PointPtr point1, PointPtr point2) override;
    };

    /**
     * @brief Create new distance algorithm based on euclidean distance.
     * @return The distance algorithm.
     */
    inline DistanceAlgorithmPtr makeEuclideanDistance()
    {
        return std::make_shared<EuclideanDistance>();
    }
}

#endif // FRTS_EUCLIDEANDISTANCE_H
