#include "AStar.h"

#include <main/ModelIds.h>
#include <main/RegionManager.h>

#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>


frts::AStar::AStar(DistanceAlgorithmPtr distanceAlgorithm)
    : distanceAlgorithm{distanceAlgorithm}
{
}

frts::PathFinder::Path frts::AStar::findPath(PointPtr start, PointPtr goal, BlockedByPtr blockedBy, SharedManagerPtr shared)
{
    // For this exact implementation see http://www.redblobgames.com/pathfinding/a-star/implementation.html#sec-2-4

    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    using Node = std::pair<Point::length, PointPtr>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;
    frontier.emplace(0.0, start);

    std::unordered_map<PointPtr, PointPtr, PointHash, PointEqual> cameFrom;
    cameFrom[start] = start;

    std::unordered_map<PointPtr, Point::length, PointHash, PointEqual> costSoFar;
    costSoFar[start] = 0.0;

    bool found = false;
    while (!frontier.empty())
    {
        auto current = frontier.top().second;
        frontier.pop();

        if (current == goal)
        {
            found = true;
            break;
        }

        auto neighbors = regionManager->findFreeNeighbors(current, blockedBy, shared);
        for (auto next : neighbors)
        {
            // Currently there are no costs associated with moving so lets simply add one.
            auto newCost = costSoFar[current] + 1.0;

            // Is this point new or are the new costs cheaper?
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
            {
                costSoFar[next] = newCost;
                auto priority = newCost + distanceAlgorithm->distance(next, goal);
                frontier.emplace(priority, next);
                cameFrom[next] = current;
            }
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
