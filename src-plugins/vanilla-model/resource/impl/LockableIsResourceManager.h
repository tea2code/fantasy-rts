#ifndef FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H
#define FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H

#include "BaseLockableResourceManager.h"

#include <region/Region.h>
#include <pathfinding/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>


namespace frts
{
    class LockableIsResourceManager : public LockableResourceManager, public std::enable_shared_from_this<LockableIsResourceManager>
    {
    public:
        LockableIsResourceManager(const IdPtr& componentType, const RegionPtr& region, const DistanceAlgorithmPtr& distAlgo);

        void add(const EntityPtr& entity) override;
        ResourceLockPtr findNearest(const IdPtr& entityGroup, const IdPtr& resourceType, const PointPtr& pos, const SharedManagerPtr& shared) override;
        EntityPtr getEntity(const ResourceLockPtr& lock) const override;
        IdPtr getResourceType(const ResourceLockPtr& lock) const override;
        bool isValid(const ResourceLockPtr& lock) const override;
        void release(const ResourceLockPtr& lock) override;
        void remove(const EntityPtr& entity) override;

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
    inline LockableResourceManagerPtr makeLockableIsResourceManager(const IdPtr& componentType,
                                                                    const RegionPtr& region,
                                                                    const DistanceAlgorithmPtr& distAlgo)
    {
        assert(componentType != nullptr);
        assert(region != nullptr);
        assert(distAlgo != nullptr);

        return std::make_shared<LockableIsResourceManager>(componentType, region, distAlgo);
    }
}

#endif // FRTS_LOCKABLEISRESOURCEMANAGERIMPL_H
