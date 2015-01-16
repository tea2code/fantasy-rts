#ifndef FRTS_PATHFINDER_H
#define FRTS_PATHFINDER_H

#include "Path.h"
#include <entity/BlockedBy.h>
#include <region/Point.h>
#include <frts/shared>

#include <memory>
#include <vector>
#include <unordered_map>


namespace frts
{
    class PathFinder;

    /**
     * @brief Pointer to PathFinder.
     */
    using PathFinderPtr = std::shared_ptr<PathFinder>;

    /**
     * @brief The path finder enables to find a path in the
     *        current region between two points.
     */
    class PathFinder
    {
    public:
        virtual ~PathFinder() {}

        /**
         * @brief Tries to find a path between start and goal.
         * @param start The start position.
         * @param goal The goal.
         * @param blockedBy Indicates which entities block the path.
         * @param shared The shared manager.
         * @return The path result.
         */
        virtual PathPtr findPath(const PointPtr& start, const PointPtr& goal,
                                 const BlockedByPtr& blockedBy, const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_PATHFINDER_H
