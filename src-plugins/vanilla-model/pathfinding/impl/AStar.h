#ifndef FRTS_ASTAR_H
#define FRTS_ASTAR_H

#include <pathfinding/DistanceAlgorithm.h>
#include <pathfinding/PathFinder.h>

#include <memory>


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
        AStar(DistanceAlgorithmPtr distanceAlgorithm, IdPtr teleportType);

        Path findPath(PointPtr start, PointPtr goal, BlockedByPtr blockedBy, SharedManagerPtr shared) override;
        CostMap getLastCosts() const override;

    private:
        CostMap costSoFar;
        DistanceAlgorithmPtr distanceAlgorithm;
        IdPtr teleportType;
    };

    /**
     * @brief Create a new AStar.
     * @param distanceAlgorithm The distance algorithm to use.
     * @param teleportType Type of teleport component.
     * @return The path finder.
     */
    inline PathFinderPtr makeAStar(DistanceAlgorithmPtr distanceAlgorithm, IdPtr teleportType)
    {
        return std::make_shared<AStar>(distanceAlgorithm, teleportType);
    }
}

#endif // FRTS_ASTAR_H
