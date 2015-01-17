#include "AStar.h"

#include "PathImpl.h"
#include <entity/Teleport.h>
#include <main/ModelIds.h>

#include <frts/timer.h>

#include <boost/format.hpp>

#include <algorithm>
#include <functional>
#include <queue>
#include <utility>


frts::AStar::AStar(const DistanceAlgorithmPtr& distanceAlgorithm, const IdPtr& teleportType)
    : distanceAlgorithm{distanceAlgorithm}, teleportType{teleportType}
    #ifdef A_STAR_BENCHMARK
    ,findNeighborsTime{0}, loopTime{0}, teleportTime{0}, totalTime{0}, walkTime{0}
    #endif
{}

frts::PathPtr frts::AStar::findPath(const PointPtr& start, const PointPtr& goal,
                                    const BlockedByPtr& blockedBy, const SharedManagerPtr& shared)
{
    assert(start != nullptr);
    assert(goal != nullptr);
    assert(shared != nullptr);

    // For this exact implementation see http://www.redblobgames.com/pathfinding/a-star/implementation.html#sec-2-4

    auto startTotal = highResTime();

    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    using Node = std::pair<Point::length, PointPtr>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;
    frontier.emplace(0.0, start);

    std::unordered_map<PointPtr, PointPtr> cameFrom;
    cameFrom[start] = start;

    costSoFar.clear();
    costSoFar[start] = 0.0;

    #ifdef A_STAR_BENCHMARK
    auto startLoop = highResTime();
    #endif

    PathPtr result = nullptr;
    bool found = false;

    // Check if the goal itself is blocking.
    auto block = regionManager->getBlock(goal, shared);
    if (!block->isBlocking(blockedBy))
    {
        while (!frontier.empty())
        {
            // Get next position.
            auto current = frontier.top().second;
            frontier.pop();

            // Reached goal?
            if (current == goal)
            {
                found = true;
                break;
            }

            // Find neighbors.
            auto neighbors = findNeighbors(current, blockedBy, regionManager, shared);

            #ifdef A_STAR_BENCHMARK
            auto startWalk = highResTime();
            #endif

            // "Walk" neighbors.
            for (auto& next : neighbors)
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

            #ifdef A_STAR_BENCHMARK
            walkTime += (highResTime() - startWalk);
            #endif
        }
    }

    #ifdef A_STAR_BENCHMARK
    loopTime += (highResTime() - startLoop);
    #endif

    // Reconstruct path.
    Path::PathPart path;
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

        result = makePath(path, true, costSoFar);
    }
    else
    {
        result = makePath({}, false, costSoFar);
    }

    #ifdef A_STAR_BENCHMARK
    totalTime += (highResTime() - startTotal);
    auto msg = boost::format(R"(findNeighborsTime = %1%ms, loopTime = %2%ms, teleportTime = %3%ms, totalTime = %4%ms, walkTime = %5%ms, found = %6%, length = %7%)")
            % findNeighborsTime.count() % loopTime.count() % teleportTime.count()
            % totalTime.count() % walkTime.count() % found % path.size();
    shared->getLog()->info("frts::A*-Benchmark", msg.str());
    #else
    #ifndef UNIT_TEST
    auto totalTime = (highResTime() - startTotal);
    if (found)
    {
        auto msg = boost::format(R"(Path found in %1%ms from (%2%, %3%, %4%) to (%5%, %6%, %7%) with a path length of %8% in frame %9%.)")
                % totalTime.count()
                % start->getX() % start->getY() % start->getZ()
                % goal->getX() % goal->getY() % goal->getZ()
                % path.size()
                % shared->getFrame()->getNumber();
        shared->getLog()->debug("frts::A*", msg.str());
    }
    else
    {
        auto msg = boost::format(R"(No path found in %1%ms from (%2%, %3%, %4%) to (%5%, %6%, %7%) in frame %8%.)")
                % totalTime.count()
                % start->getX() % start->getY() % start->getZ()
                % goal->getX() % goal->getY() % goal->getZ()
                % shared->getFrame()->getNumber();
        shared->getLog()->debug("frts::A*", msg.str());
    }
    #endif
    #endif

    return result;
}

std::vector<frts::PointPtr> frts::AStar::findNeighbors(const PointPtr& current, const BlockedByPtr& blockedBy,
                                                       const RegionManagerPtr& regionManager,
                                                       const SharedManagerPtr& shared)
{
    assert(current != nullptr);
    assert(regionManager != nullptr);
    assert(shared != nullptr);

    #ifdef A_STAR_BENCHMARK
    auto startFindNeighbors = highResTime();
    #endif

    // Get neighbors from same z-level.
    auto neighbors = regionManager->findFreeNeighbors(current, blockedBy, true, shared);

    #ifdef A_STAR_BENCHMARK
    findNeighborsTime += (highResTime() - startFindNeighbors);
    #endif

    #ifdef A_STAR_BENCHMARK
    auto startTeleport = highResTime();
    #endif

    // Does an entity at the current position have a teleport component?
    auto block = regionManager->getBlock(current, shared);
    auto teleportEntities = block->getByComponent(teleportType);
    for (auto& entity : teleportEntities)
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

    #ifdef A_STAR_BENCHMARK
    teleportTime += (highResTime() - startTeleport);
    #endif

    return neighbors;
}
