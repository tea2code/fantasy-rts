#ifndef FRTS_LOCKABLERESOURCEMANAGER_H
#define FRTS_LOCKABLERESOURCEMANAGER_H

#include "ResourceLock.h"


namespace frts
{
    class LockableResourceManager
    {
    public:
        virtual ~LockableResourceManager() {}

        virtual ResourceLockPtr findNearest(IdPtr type, PointPtr pos) = 0;

    protected:
        virtual void release(ResourceLock lock) = 0;
    };
}

#endif // FRTS_LOCKABLERESOURCEMANAGER_H
