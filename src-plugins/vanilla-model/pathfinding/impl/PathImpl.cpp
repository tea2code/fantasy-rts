#include "PathImpl.h"


frts::PathImpl::PathImpl(Path::PathPart path, bool exists, Path::CostMap costs, Path::BenchmarkMap timings)
    : costs{costs}, exists{exists}, path{path}, timings{timings}
{
}

frts::Path::PathPart frts::PathImpl::getCompletePath() const
{
    return path;
}

frts::Path::CostMap frts::PathImpl::getCosts() const
{
    return costs;
}

frts::PointPtr frts::PathImpl::getNextPathPos()
{
    if (path.empty() || pathIndex + 1 == path.size())
    {
        return nullptr;
    }
    else
    {
        pathIndex += 1;
        return path.at(pathIndex);
    }
}

frts::PointPtr frts::PathImpl::getPreviousPathPos() const
{
    if (path.empty() || pathIndex == 0)
    {
        return nullptr;
    }
    else
    {
        return path.at(pathIndex - 1);
    }
}

frts::Path::BenchmarkMap frts::PathImpl::getTimings() const
{
    return timings;
}

bool frts::PathImpl::pathExists() const
{
    return exists;
}
