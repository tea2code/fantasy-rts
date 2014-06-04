#ifndef FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H
#define FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H

#include "BaseLockableResourceManager.h"

#include <region/Region.h>
#include <resource/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>


namespace frts
{
    class LockableIsResourceManagerImpl : public LockableResourceManager, public std::enable_shared_from_this<LockableIsResourceManagerImpl>
    {
    public:
        LockableIsResourceManagerImpl(IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo);

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
     * @brief Create new LockableResourceManager for IsResource component.
     * @param componentType The component type.
     * @param region The region in which this resource manager operates.
     * @param distAlgo The distance algorithm used to calculate the nearest resource.
     * @return The resource manager.
     */
    inline LockableResourceManagerPtr makeLockableIsResourceManager(IdPtr componentType, RegionPtr region, DistanceAlgorithmPtr distAlgo)
    {
        return std::make_shared<LockableIsResourceManagerImpl>(componentType, region, distAlgo);
    }
}

#endif // FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H
