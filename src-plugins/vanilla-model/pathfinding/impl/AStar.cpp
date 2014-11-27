#include "AStar.h"

#include <entity/Teleport.h>
#include <main/ModelIds.h>
#include <main/RegionManager.h>

//#include <easylogging++.h>

//_INITIALIZE_EASYLOGGINGPP

#include <algorithm>
#include <functional>
#include <queue>
#include <utility>


frts::AStar::AStar(DistanceAlgorithmPtr distanceAlgorithm, IdPtr teleportType)
    : distanceAlgorithm{distanceAlgorithm}, teleportType{teleportType}
{
}

frts::PathFinder::Path frts::AStar::findPath(PointPtr start, PointPtr goal, BlockedByPtr blockedBy, SharedManagerPtr shared)
{
//    TIMED_FUNC(pathfinding);

    // For this exact implementation see http://www.redblobgames.com/pathfinding/a-star/implementation.html#sec-2-4

    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    using Node = std::pair<Point::length, PointPtr>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;
    frontier.emplace(0.0, start);

    std::unordered_map<PointPtr, PointPtr, PointHash, PointEqual> cameFrom;
    cameFrom[start] = start;

    costSoFar.clear();
    costSoFar[start] = 0.0;

    bool found = false;

    // Check if the goal itself is blocking.
    auto block = regionManager->getBlock(goal, shared);
    if (!block->isBlocking(blockedBy))
    {
        while (!frontier.empty())
        {
            auto current = frontier.top().second;
            frontier.pop();

            if (current == goal)
            {
                found = true;
                break;
            }

            // Get neighbors from same z-level.
//            PERFORMANCE_CHECKPOINT_WITH_ID(pathfinding, "before neighbors");
            auto neighbors = regionManager->findFreeNeighbors(current, blockedBy, true, shared);
//            PERFORMANCE_CHECKPOINT_WITH_ID(pathfinding, "after neighbors");

            // Does an entity at the current position have a teleport component?
            auto block = regionManager->getBlock(current, shared);
            auto teleportEntities = block->getByComponent(teleportType);
            for (auto entity : teleportEntities)
            {
                auto teleport = getComponent<Teleport>(teleportType, entity);
                auto target = teleport->getTarget();
                if (target == nullptr)
                {
                    continue;
                }

                auto teleportPos = regionManager->getPos(target, shared);
                if (teleportPos == nullptr)
                {
                    continue;
                }

                block = regionManager->getBlock(teleportPos, shared);
                if (!block->isBlocking(blockedBy))
                {
                    neighbors.push_back(teleportPos);
                }
            }

            // "Walk" neighbors.
//            PERFORMANCE_CHECKPOINT_WITH_ID(pathfinding, "before walk");
            for (auto next : neighbors)
            {
                // Currently there are no costs associated with moving so lets simply add one.
                Point::length newCost = costSoFar[current] + 1.0;

                // Is this point new or are the new costs cheaper?
                if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
                {
                    costSoFar[next] = newCost;
                    Point::length priority = newCost + distanceAlgorithm->distance(next, goal);
                    frontier.emplace(priority, next);
                    cameFrom[next] = current;
                }
            }
//            PERFORMANCE_CHECKPOINT_WITH_ID(pathfinding, "after walk");
        }
    }

    // Reconstruct path.
    PathFinder::Path path;
    if (found)
    {
        auto current = goal;
        path.push_back(current);
        while (current != start)
        {
            current = cameFrom[current];
            path.push_back(current);
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}

frts::AStar::CostMap frts::AStar::getLastCosts() const
{
    return costSoFar;
}
