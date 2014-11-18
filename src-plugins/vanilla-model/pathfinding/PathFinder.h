#ifndef FRTS_PATHFINDER_H
#define FRTS_PATHFINDER_H

#include <entity/BlockedBy.h>
#include <region/Point.h>

#include <frts/shared>

#include <memory>
#include <vector>


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
        /**
         * @brief A path consisting of individual positions.
         */
        using Path = std::vector<PointPtr>;

    public:
        virtual ~PathFinder() {}

        /**
         * @brief Tries to find a path between start and goal.
         * @param start The start position.
         * @param goal The goal.
         * @param blockedBy Indicates which entities block the path.
         * @param shared The shared manager.
         * @return A path if possible or empty if no path is found.
         */
        virtual Path findPath(PointPtr start, PointPtr goal, BlockedBy blockedBy, SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_PATHFINDER_H
