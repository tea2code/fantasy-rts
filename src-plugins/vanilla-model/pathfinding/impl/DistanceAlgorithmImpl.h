#ifndef FRTS_DISTANCEALGORITHMIMPL_H
#define FRTS_DISTANCEALGORITHMIMPL_H

#include <pathfinding/DistanceAlgorithm.h>


namespace frts
{
    class DistanceAlgorithmImpl : public DistanceAlgorithm
    {
    public:
        DistanceAlgorithmImpl();

        Point::length distance(PointPtr point1, PointPtr point2) override;
    };

    /**
     * @brief Create new distance algorithm.
     * @return The distance algorithm.
     */
    inline DistanceAlgorithmPtr makeDistanceAlgorithm()
    {
        return std::make_shared<DistanceAlgorithmImpl>();
    }
}

#endif // FRTS_DISTANCEALGORITHMIMPL_H
