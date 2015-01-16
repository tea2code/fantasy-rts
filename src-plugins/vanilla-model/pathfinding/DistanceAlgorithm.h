#ifndef FRTS_DISTANCEALGORITHM_H
#define FRTS_DISTANCEALGORITHM_H

#include <region/Point.h>

#include <memory>


namespace frts
{
    class DistanceAlgorithm;

    /**
     * @brief Pointer to DistanceAlgorithm.
     */
    using DistanceAlgorithmPtr = std::shared_ptr<DistanceAlgorithm>;

    /**
     * @brief Distance algorithm can be used in implementations of the resource
     *        manager to check the distance between a starting point and resources.
     *        This interface can also be used in pathfinding...
     */
    class DistanceAlgorithm
    {
    public:
        virtual ~DistanceAlgorithm() {}

        /**
         * @brief Calculate the distance between two points.
         * @param point1 First point.
         * @param point2 Second point.
         * @return The distance.
         */
        virtual Point::length distance(const PointPtr& point1, const PointPtr& point2) = 0;
    };
}

#endif // FRTS_DISTANCEALGORITHM_H
