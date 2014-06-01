#include "LockableHasResourceManagerImpl.h"

frts::LockableHasResourceManagerImpl::LockableHasResourceManagerImpl()
{
}

void frts::LockableHasResourceManagerImpl::add(EntityPtr entity)
{

}

frts::ResourceLockPtr frts::LockableHasResourceManagerImpl::findNearest(
        IdPtr entityGroup, IdPtr resourceType, PointPtr pos)
{
    return nullptr;
}

frts::EntityPtr frts::LockableHasResourceManagerImpl::getEntity(ConstResourceLockPtr lock) const
{
    return nullptr;
}

frts::IdPtr frts::LockableHasResourceManagerImpl::getResourceType(ConstResourceLockPtr lock) const
{
    return nullptr;
}

bool frts::LockableHasResourceManagerImpl::isValid(ConstResourceLockPtr lock) const
{
    return false;
}

void frts::LockableHasResourceManagerImpl::release(ResourceLockPtr lock)
{

}

void frts::LockableHasResourceManagerImpl::remove(EntityPtr entity)
{

}

