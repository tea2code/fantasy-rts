#ifndef FRTS_ENTITYGROUPSATELLITE
#define FRTS_ENTITYGROUPSATELLITE

#include "Component.h"
#include "Entity.h"

#include <memory>


namespace frts
{
    class EntityGroupSatellite;

    /**
     * @brief Pointer to EntityGroupSatellite.
     */
    using EntityGroupSatellitePtr = std::shared_ptr<EntityGroupSatellite>;

    /**
     * @brief The component of entity group satellites.
     *        Will be created implicitly by EntityGroup and cannot be created in any method of
     *        model factory. Has a weak reference to its master.
     */
    class EntityGroupSatellite : public Component
    {
    public:
        virtual ~EntityGroupSatellite() {}

        /**
         * @brief Get the entity group master.
         * @return The master entity.
         */
        virtual EntityPtr getMaster() const = 0;
    };
}

#endif // FRTS_ENTITYGROUPSATELLITE

