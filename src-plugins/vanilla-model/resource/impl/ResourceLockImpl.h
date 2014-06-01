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
        ~ResourceLockImpl() override;

        EntityPtr getEntity() const override;
        IdPtr getResourceType() const override;
        bool isValid() const override;
        void release() override;

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
