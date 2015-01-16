#ifndef FRTS_TELEPORT_H
#define FRTS_TELEPORT_H

#include "Component.h"
#include "Entity.h"

#include <memory>


namespace frts
{
    class Teleport;

    /**
     * @brief Pointer to Teleport.
     */
    using TeleportPtr = std::shared_ptr<Teleport>;

    /**
     * @brief Component creates virtualle connected entities which represent for example
     *        a portal, a ramp or a slope.
     */
    class Teleport : public Component
    {
    public:
        virtual ~Teleport() {}

        /**
         * @brief Get the target of this component.
         * @return The target entity or null if no target is set.
         */
        virtual EntityPtr getTarget() const = 0;

        /**
         * @brief Set the target of this component.
         * @param entity The target entity.
         */
        virtual void setTarget(const EntityPtr& target) = 0;
    };
}

#endif // FRTS_TELEPORT_H
