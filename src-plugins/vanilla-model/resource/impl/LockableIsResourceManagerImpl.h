#ifndef FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H
#define FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H

#include <region/Region.h>
#include <resource/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>


namespace frts
{
    class LockableIsResourceManagerImpl : public LockableResourceManager
    {
    public:
        LockableIsResourceManagerImpl(RegionPtr region, DistanceAlgorithmPtr distAlgo);

        void add(EntityPtr entity);
        ResourceLockPtr findNearest(IdPtr entityGroup, IdPtr resourceType, PointPtr pos);
        EntityPtr getEntity(ConstResourceLockPtr lock) const;
        IdPtr getResourceType(ConstResourceLockPtr lock) const;
        bool isValid(ConstResourceLockPtr lock) const;
        void release(ResourceLockPtr lock);
        void remove(EntityPtr entity);

    private:
        DistanceAlgorithmPtr distAlgo;
        RegionPtr region;
    };

    /**
     * @brief Create new LockableResourceManager for IsResource component.
     * @param region The region in which this resource manager operates.
     * @param distAlgo The distance algorithm used to calculate the nearest resource.
     * @return The resource manager.
     */
    inline LockableResourceManagerPtr makeLockableIsResourceManager(RegionPtr region, DistanceAlgorithmPtr distAlgo)
    {
        return std::make_shared<LockableIsResourceManagerImpl>(region, distAlgo);
    }
}

#endif // FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H
