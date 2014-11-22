#ifndef FRTS_ASTAR_H
#define FRTS_ASTAR_H

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
     */
    class AStar : public PathFinder
    {
    public:
        AStar();

        Path findPath(PointPtr start, PointPtr goal, BlockedByPtr blockedBy, SharedManagerPtr shared) override;
    };

    /**
     * @brief Create a new AStar.
     * @return The path finder.
     */
    inline PathFinderPtr makeAStar()
    {
        return std::make_shared<AStar>();
    }
}

#endif // FRTS_ASTAR_H
