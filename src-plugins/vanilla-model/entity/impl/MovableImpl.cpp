#include "MovableImpl.h"

frts::MovableImpl::MovableImpl(IdPtr type)
    : type{type}
{
}

frts::IdPtr frts::MovableImpl::getComponentType() const
{
    return type;
}

frts::Movable::Direction frts::MovableImpl::getDirection() const
{
    return Direction::South;
}

frts::PathFinder::Path frts::MovableImpl::getPath() const
{
    return {};
}

frts::PointPtr frts::MovableImpl::getNextPathPos() const
{
    return nullptr;
}

frts::PointPtr frts::MovableImpl::getPreviousPathPos() const
{
    return nullptr;
}

void frts::MovableImpl::setPath(PathFinder::Path path)
{

}
