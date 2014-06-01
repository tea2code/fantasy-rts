#include "ResourceLockImpl.h"


frts::ResourceLockImpl::ResourceLockImpl(LockableResourceManagerPtr manager)
    : manager{manager}
{
}

frts::ResourceLockImpl::~ResourceLockImpl()
{
    release();
}

frts::EntityPtr frts::ResourceLockImpl::getEntity() const
{
    return manager->getEntity(shared_from_this());
}

frts::IdPtr frts::ResourceLockImpl::getResourceType() const
{
    return manager->getResourceType(shared_from_this());
}

bool frts::ResourceLockImpl::isValid() const
{
    return manager->isValid(shared_from_this());
}

void frts::ResourceLockImpl::release()
{
    if (!isValid())
    {
        return;
    }

    manager->release(shared_from_this());
}
