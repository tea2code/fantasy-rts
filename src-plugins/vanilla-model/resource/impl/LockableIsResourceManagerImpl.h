#ifndef FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H
#define FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H

#include <resource/LockableResourceManager.h>


namespace frts
{
    class LockableIsResourceManagerImpl : public LockableResourceManager
    {
    public:
        LockableIsResourceManagerImpl();

        void add(EntityPtr entity);
        ResourceLockPtr findNearest(IdPtr entityGroup, IdPtr resourceType, PointPtr pos);
        EntityPtr getEntity(ConstResourceLockPtr lock) const;
        IdPtr getResourceType(ConstResourceLockPtr lock) const;
        bool isValid(ConstResourceLockPtr lock) const;
        void release(ResourceLockPtr lock);
        void remove(EntityPtr entity);
    };

    /**
     * @brief Create new LockableResourceManager for IsResource component.
     * @return The resource manager.
     */
    inline LockableResourceManagerPtr makeLockableIsResourceManager()
    {
        return std::make_shared<LockableIsResourceManagerImpl>();
    }
}

#endif // FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H
