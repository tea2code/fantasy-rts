#ifndef FRTS_ENTITYGROUPSATELLITEIMPL_H
#define FRTS_ENTITYGROUPSATELLITEIMPL_H

#include <entity/EntityGroupSatellite.h>

#include <memory>


namespace frts
{
    class EntityGroupSatelliteImpl : public EntityGroupSatellite
    {
    public:
        /**
         * @param componentType The component type.
         * @param master The entity group master.
         */
        EntityGroupSatelliteImpl(const IdPtr& componentType, const EntityPtr& master);
        ~EntityGroupSatelliteImpl();

        IdPtr getComponentType() const override;
        EntityPtr getMaster() const override;

    private:
        IdPtr componentType;

        std::weak_ptr<Entity> master;
    };

    /**
     * @brief Create new EntityGroupSatellite.
     * @param componentType The component type.
     * @param master The entity group master.
     * @return The component.
     */
    inline ComponentPtr makeEntityGroupSatellite(const IdPtr& componentType, const EntityPtr& master)
    {
        assert(componentType != nullptr);
        assert(master != nullptr);

        return std::make_shared<EntityGroupSatelliteImpl>(componentType, master);
    }
}

#endif // FRTS_ENTITYGROUPSATELLITEIMPL_H
