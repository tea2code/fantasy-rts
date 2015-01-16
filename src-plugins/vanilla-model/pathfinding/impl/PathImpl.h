#ifndef FRTS_PATHIMPL_H
#define FRTS_PATHIMPL_H

#include <pathfinding/Path.h>

#include <memory>


namespace frts
{
    class PathImpl : public Path
    {
    public:
        /**
         * @param path The complete path.
         * @param exists Should be true if path was found.
         * @param costs The costs map for debugging.
         * @param timings The timings map for debugging.
         */
        PathImpl(const Path::PathPart& path, bool exists, const Path::CostMap& costs = Path::CostMap(),
                 const Path::BenchmarkMap& timings = Path::BenchmarkMap());

        PathPart getCompletePath() const;
        CostMap getCosts() const;
        PointPtr getNextPathPos();
        PointPtr getPreviousPathPos() const;
        BenchmarkMap getTimings() const;
        bool pathExists() const;

    private:
        CostMap costs;
        bool exists;
        PathPart path;
        PathPart::size_type pathIndex = 0;
        BenchmarkMap timings;
    };

    /**
     * @brief Create new Path.
     * @param path The complete path.
     * @param exists Should be true if path was found.
     * @param costs The costs map for debugging.
     * @param timings The timings map for debugging.
     * @return The new Path.
     */
    inline PathPtr makePath(const Path::PathPart& path, bool exists, const Path::CostMap& costs = Path::CostMap(),
                            const Path::BenchmarkMap& timings = Path::BenchmarkMap())
    {
        return std::make_shared<PathImpl>(path, exists, costs, timings);
    }
}

#endif // FRTS_PATHIMPL_H
