#ifndef FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H
#define FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H

#include "BaseLockableResourceManager.h"

#include <region/Region.h>
#include <resource/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>


namespace frts
{
    class LockableHasResourceManagerImpl : public LockableResourceManager, public std::enable_shared_from_this<LockableHasResourceManagerImpl>
    {
    public:
        LockableHasResourceManagerImpl(IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo);

        void add(EntityPtr entity) override;
        ResourceLockPtr findNearest(IdPtr entityGroup, IdPtr resourceType, PointPtr pos) override;
        EntityPtr getEntity(ResourceLockPtr lock) const override;
        IdPtr getResourceType(ResourceLockPtr lock) const override;
        bool isValid(ResourceLockPtr lock) const override;
        void release(ResourceLockPtr lock) override;
        void remove(EntityPtr entity) override;

    private:
        IdPtr componentType;
        BaseLockableResourceManager resourceManager;
    };

    /**
     * @brief Create new LockableResourceManager for HasResource component.
     * @param componentType The component type.
     * @param region The region in which this resource manager operates.
     * @param distAlgo The distance algorithm used to calculate the nearest resource.
     * @return The resource manager.
     */
    inline LockableResourceManagerPtr makeLockableHasResourceManager(
            IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo)
    {
        return std::make_shared<LockableHasResourceManagerImpl>(componentType, region, distAlgo);
    }
}

#endif // FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H
