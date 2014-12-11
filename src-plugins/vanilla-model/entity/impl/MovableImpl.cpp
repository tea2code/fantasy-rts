#include "MovableImpl.h"

frts::MovableImpl::MovableImpl(IdPtr type)
    : current{nullptr}, path{nullptr}, previous{nullptr}, type{type}
{}

frts::IdPtr frts::MovableImpl::getComponentType() const
{
    return type;
}

frts::Movable::Direction frts::MovableImpl::getDirection() const
{
    auto result = Direction::South;
    if (previous != nullptr && current != nullptr)
    {
        auto dx = current->getX() - previous->getX();
        auto dy = current->getY() - previous->getY();

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

frts::PathPtr frts::MovableImpl::getPath() const
{
    return path;
}

frts::PointPtr frts::MovableImpl::getNextPathPos()
{
    if (path == nullptr)
    {
        return nullptr;
    }
    current = path->getNextPathPos();
    previous = path->getPreviousPathPos();
    return current;
}

frts::PointPtr frts::MovableImpl::getPreviousPathPos() const
{
    return previous;
}

void frts::MovableImpl::setPath(PathPtr path)
{
    this->path = path;
    previous = nullptr;
    current = nullptr;
}
