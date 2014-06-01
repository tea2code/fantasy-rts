#ifndef FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H
#define FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H

#include <resource/LockableResourceManager.h>


namespace frts
{
    class LockableHasResourceManagerImpl : public LockableResourceManager
    {
    public:
        LockableHasResourceManagerImpl();

        void add(EntityPtr entity);
        ResourceLockPtr findNearest(IdPtr entityGroup, IdPtr resourceType, PointPtr pos);
        EntityPtr getEntity(ConstResourceLockPtr lock) const;
        IdPtr getResourceType(ConstResourceLockPtr lock) const;
        bool isValid(ConstResourceLockPtr lock) const;
        void release(ResourceLockPtr lock);
        void remove(EntityPtr entity);
    };

    /**
     * @brief Create new LockableResourceManager for HasResource component.
     * @return The resource manager.
     */
    inline LockableResourceManagerPtr makeLockableHasResourceManager()
    {
        return std::make_shared<LockableHasResourceManagerImpl>();
    }
}

#endif // FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H
