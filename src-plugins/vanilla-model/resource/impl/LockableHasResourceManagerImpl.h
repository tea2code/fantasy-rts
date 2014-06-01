#ifndef FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H
#define FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H

#include <region/Region.h>
#include <resource/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>


namespace frts
{
    class LockableHasResourceManagerImpl : public LockableResourceManager
    {
    public:
        LockableHasResourceManagerImpl(RegionPtr region, DistanceAlgorithmPtr distAlgo);

        void add(EntityPtr entity) override;
        ResourceLockPtr findNearest(IdPtr entityGroup, IdPtr resourceType, PointPtr pos) override;
        EntityPtr getEntity(ConstResourceLockPtr lock) const override;
        IdPtr getResourceType(ConstResourceLockPtr lock) const override;
        bool isValid(ConstResourceLockPtr lock) const override;
        void release(ResourceLockPtr lock) override;
        void remove(EntityPtr entity) override;

    private:
        DistanceAlgorithmPtr distAlgo;
        RegionPtr region;
    };

    /**
     * @brief Create new LockableResourceManager for HasResource component.
     * @param region The region in which this resource manager operates.
     * @param distAlgo The distance algorithm used to calculate the nearest resource.
     * @return The resource manager.
     */
    inline LockableResourceManagerPtr makeLockableHasResourceManager(RegionPtr region, DistanceAlgorithmPtr distAlgo)
    {
        return std::make_shared<LockableHasResourceManagerImpl>(region, distAlgo);
    }
}

#endif // FRTS_LOCKABLEHASRESOURCEMANAGERIMPL_H
