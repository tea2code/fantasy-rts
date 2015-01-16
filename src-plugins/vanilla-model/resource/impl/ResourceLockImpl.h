#ifndef FRTS_RESOURCELOCKIMPL_H
#define FRTS_RESOURCELOCKIMPL_H

#include <resource/LockableResourceManager.h>
#include <resource/ResourceLock.h>


namespace frts
{
    class ResourceLockImpl : public ResourceLock, public std::enable_shared_from_this<ResourceLockImpl>
    {
    public:
        ResourceLockImpl(const LockableResourceManagerPtr& manager);
        ~ResourceLockImpl() override;

        EntityPtr getEntity() const override;
        IdPtr getResourceType() const override;
        bool isValid() const override;
        void release() override;

    private:
        bool isReleased;
        LockableResourceManagerPtr manager;
    };

    /**
     * @brief Custom deleter for usage of ResourceLock with smart pointers.
     */
    struct ResourceLockDeleter
    {
        void operator()(ResourceLockImpl* p)
        {
            // First release lock then delete it.
            p->release();
            delete p;
        }
    };

    /**
     * @brief Create new ResourceLock.
     * @param manager The resource manager of this lock.
     * @return The resource lock.
     */
    inline ResourceLockPtr makeResourceLock(const LockableResourceManagerPtr& manager)
    {
        assert(manager != nullptr);

        return std::shared_ptr<ResourceLockImpl>(new ResourceLockImpl(manager), ResourceLockDeleter());
    }
}

#endif // RESOURCELOCKIMPL_H
