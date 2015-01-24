#ifndef FRTS_ENTITYGROUPIMPL_H
#define FRTS_ENTITYGROUPIMPL_H

#include <entity/EntityGroup.h>

#include <unordered_map>


namespace frts
{
    class EntityGroupImpl : public EntityGroup
    {
    public:
        using EntityPosMap = std::unordered_map<EntityPtr, PointPtr>;

    public:
        /**
         * @param componentType The component type.
         * @param satellites The satellites.
         * @param positions The relative positions of all satellites.
         */
        EntityGroupImpl(IdPtr componentType, EntityVector satellites, EntityPosMap positions);
        ~EntityGroupImpl();

        IdPtr getComponentType() const override;
        EntityVector getSatellites() const override;
        PointPtr getSatellitePos(EntityPtr satellite) const override;

    private:
        IdPtr componentType;

        EntityVector satellites;
        EntityPosMap positions;
    };

    /**
     * @brief Create new EntityGroup.
     * @param componentType The component type.
     * @param satellites The satellites.
     * @param positions The relative positions of all satellites.
     * @return The component.
     */
    inline ComponentPtr makeEntityGroup(IdPtr componentType, EntityVector satellites = {},
                                        EntityGroupImpl::EntityPosMap positions = EntityGroupImpl::EntityPosMap())
    {
        assert(componentType != nullptr);

        return std::make_shared<EntityGroupImpl>(componentType, satellites, positions);
    }
}

#endif // FRTS_ENTITYGROUPIMPL_H
