#ifndef FRTS_ENTITYGROUP
#define FRTS_ENTITYGROUP

#include "Component.h"
#include "Entity.h"
#include <region/Point.h>

#include <memory>


namespace frts
{
    class EntityGroup;

    /**
     * @brief Pointer to EntityGroup.
     */
    using EntityGroupPtr = std::shared_ptr<EntityGroup>;

    /**
     * @brief This components indicates the master entity of an entity group. It stores all
     *        the satellite entities and their relative positions.
     */
    class EntityGroup : public Component
    {
    public:
        virtual ~EntityGroup() {}

        /**
         * @brief Get a list of all satellite entities.
         * @return The satellites.
         */
        virtual EntityVector getSatellites() const = 0;

        /**
         * @brief Get the position of given satellite.
         * @param satellite The satellite entity.
         * @return The position.
         */
        virtual PointPtr getSatellitePos(const EntityPtr& satellite) const = 0;
    };
}

#endif // FRTS_ENTITYGROUP

