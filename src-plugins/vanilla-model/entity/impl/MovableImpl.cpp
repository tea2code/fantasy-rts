#include "MovableImpl.h"

frts::MovableImpl::MovableImpl(IdPtr type)
    : type{type}
{}

frts::IdPtr frts::MovableImpl::getComponentType() const
{
    return type;
}

frts::Movable::Direction frts::MovableImpl::getDirection() const
{
    auto result = Direction::South;
    if (!path.empty() && pathIndex > 0)
    {
        auto posPrevious = path.at(pathIndex - 1);
        auto pos = path.at(pathIndex);
        auto dx = pos->getX() - posPrevious->getX();
        auto dy = pos->getY() - posPrevious->getY();

        if (dx > 0)
        {
            result = Direction::East;
        }
        else if (dx < 0)
        {
            result = Direction::West;
        }
        else if (dy < 0)
        {
            result = Direction::North;
        }
    }
    return result;
}

frts::PathFinder::Path frts::MovableImpl::getPath() const
{
    return path;
}

frts::PointPtr frts::MovableImpl::getNextPathPos()
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

frts::PointPtr frts::MovableImpl::getPreviousPathPos() const
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

void frts::MovableImpl::setPath(PathFinder::Path path)
{
    this->path = path;
    pathIndex = 0;
}
