#ifndef FRTS_ASTAR_H
#define FRTS_ASTAR_H

#include <main/RegionManager.h>
#include <pathfinding/DistanceAlgorithm.h>
#include <pathfinding/PathFinder.h>

#include <chrono>
#include <memory>
#include <vector>


namespace frts
{
    class AStar;

    /**
     * @brief Pointer to AStar
     */
    using AstarPtr = std::shared_ptr<AStar>;

    /**
     * @brief Implementation of path finding using
     *        the A* algorithm.
     * @see http://theory.stanford.edu/~amitp/GameProgramming/
     * @param distanceAlgorithm The distance algorithm to use.
     * @param teleportType Type of teleport component.
     */
    class AStar : public PathFinder
    {
    public:
        AStar(const DistanceAlgorithmPtr& distanceAlgorithm, const IdPtr& teleportType);

        PathPtr findPath(const PointPtr& start, const PointPtr& goal, const BlockedByPtr& blockedBy, const SharedManagerPtr& shared) override;

    private:
        Path::CostMap costSoFar;
        DistanceAlgorithmPtr distanceAlgorithm;
        IdPtr teleportType;

        #ifdef A_STAR_BENCHMARK
        std::chrono::milliseconds findNeighborsTime;
        std::chrono::milliseconds loopTime;
        std::chrono::milliseconds teleportTime;
        std::chrono::milliseconds totalTime;
        std::chrono::milliseconds walkTime;
        #endif

    private:
        PointVector findNeighbors(const PointPtr& current, const BlockedByPtr& blockedBy,
                                  const RegionManagerPtr& regionManager, const SharedManagerPtr& shared);
    };

    /**
     * @brief Create a new AStar.
     * @param distanceAlgorithm The distance algorithm to use.
     * @param teleportType Type of teleport component.
     * @return The path finder.
     */
    inline PathFinderPtr makeAStar(const DistanceAlgorithmPtr& distanceAlgorithm, const IdPtr& teleportType)
    {
        assert(distanceAlgorithm != nullptr);
        assert(teleportType != nullptr);

        return std::make_shared<AStar>(distanceAlgorithm, teleportType);
    }
}

#endif // FRTS_ASTAR_H
