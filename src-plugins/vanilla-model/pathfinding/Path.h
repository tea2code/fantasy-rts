#ifndef FRTS_PATH_H
#define FRTS_PATH_H

#include <region/Point.h>

#include <chrono>
#include <memory>
#include <unordered_map>
#include <vector>


namespace frts
{
    class Path;

    /**
     * @brief Pointer to Path.
     */
    using PathPtr = std::shared_ptr<Path>;

    /**
     * @brief Represents the result of a path finding operation.
     */
    class Path
    {
    public:
        /**
         * @brief For debugging purpose. A mapping of measure point names to durations.
         */
        using BenchmarkMap = std::unordered_map<std::string, std::chrono::milliseconds>;

        /**
         * @brief For debugging purpose. A mapping of points and their associated costs.
         */
        using CostMap = std::unordered_map<PointPtr, Point::length, PointHash, PointEqual>;

        /**
         * @brief A part or the complete path as a list of points.
         */
        using PathPart = PointVector;

    public:
        virtual ~Path() {}

        /**
         * @brief Get the complete path. May be expensive.
         * @return The complete path including the start and goal. An empty path indicates
         *         that either no path was found or start and goal are the same.
         */
        virtual PathPart getCompletePath() const = 0;

        /**
         * @brief For debugging purpose. The costs of the path finding search.
         * @warning Implementations are allowed to always return a empty map to reduce memory
         *          footprint. In such a case it is recommended to allow enabling this feature
         *          using a compile or runtime flag.
         * @return The costs of the path finding search.
         */
        virtual CostMap getCosts() const = 0;

        /**
         * @brief Get the next position of this path. Will move the internal current position
         *        a step forward.
         * @return The position or null if path is complete.
         */
        virtual PointPtr getNextPathPos() = 0;

        /**
         * @brief Get the previous position of this path.
         * @return The position or null if path is at the beginning.
         */
        virtual PointPtr getPreviousPathPos() const = 0;

        /**
         * @brief For debugging purpose. Get timings for benchmark usage of algorithm.
         * @return Map of timings.
         */
        virtual BenchmarkMap getTimings() const = 0;

        /**
         * @brief Indicates if a path was found.
         * @return True if path exists else false.
         */
        virtual bool pathExists() const = 0;
    };
}

#endif // FRTS_PATH_H
