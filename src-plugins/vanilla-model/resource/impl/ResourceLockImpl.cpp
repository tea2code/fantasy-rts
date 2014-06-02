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
    return manager->getEntity(std::const_pointer_cast<ResourceLockImpl>(shared_from_this()));
}

frts::IdPtr frts::ResourceLockImpl::getResourceType() const
{
    return manager->getResourceType(std::const_pointer_cast<ResourceLockImpl>(shared_from_this()));
}

bool frts::ResourceLockImpl::isValid() const
{
    return manager->isValid(std::const_pointer_cast<ResourceLockImpl>(shared_from_this()));
}

void frts::ResourceLockImpl::release()
{
    if (!isValid())
    {
        return;
    }

    manager->release(shared_from_this());
}
