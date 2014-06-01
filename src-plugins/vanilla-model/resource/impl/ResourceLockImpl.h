#ifndef FRTS_RESOURCELOCKIMPL_H
#define FRTS_RESOURCELOCKIMPL_H

#include <resource/LockableResourceManager.h>
#include <resource/ResourceLock.h>


namespace frts
{
    class ResourceLockImpl : public ResourceLock, public std::enable_shared_from_this<ResourceLockImpl>
    {
    public:
        ResourceLockImpl(LockableResourceManagerPtr manager);
        ~ResourceLockImpl();

        EntityPtr getEntity() const;
        IdPtr getResourceType() const;
        bool isValid() const;
        void release();

    private:
        LockableResourceManagerPtr manager;
    };

    /**
     * @brief Create new ResourceLock.
     * @param manager The resource manager of this lock.
     * @return The resource lock.
     */
    inline ResourceLockPtr makeResourceLock(LockableResourceManagerPtr manager)
    {
        return std::make_shared<ResourceLockImpl>(manager);
    }
}

#endif // RESOURCELOCKIMPL_H
