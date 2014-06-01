#include "LockableIsResourceManagerImpl.h"


frts::LockableIsResourceManagerImpl::LockableIsResourceManagerImpl(
        RegionPtr region, DistanceAlgorithmPtr distAlgo)
    : distAlgo{distAlgo}, region{region}
{
}

void frts::LockableIsResourceManagerImpl::add(EntityPtr entity)
{

}

frts::ResourceLockPtr frts::LockableIsResourceManagerImpl::findNearest(
        IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return nullptr;
}

frts::EntityPtr frts::LockableIsResourceManagerImpl::getEntity(ConstResourceLockPtr lock) const
{
    return nullptr;
}

frts::IdPtr frts::LockableIsResourceManagerImpl::getResourceType(ConstResourceLockPtr lock) const
{
    return nullptr;
}

bool frts::LockableIsResourceManagerImpl::isValid(ConstResourceLockPtr lock) const
{
    return false;
}

void frts::LockableIsResourceManagerImpl::release(ResourceLockPtr lock)
{

}

void frts::LockableIsResourceManagerImpl::remove(EntityPtr entity)
{

}

