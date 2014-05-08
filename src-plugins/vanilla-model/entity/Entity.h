#ifndef FRTS_ENTITY_H
#define FRTS_ENTITY_H

#include "Blocking.h"

#include <frts/shared>

#include <memory>>


namespace frts
{
    class Entity;

    /**
     * @brief Pointer to Entity.
     */
    using EntityPtr = std::shared_ptr<Entity>;

    /**
     * @brief Base class of entities.
     */
    class Entity
    {
    public:
        virtual ~Entity() {}

        /**
         * @brief Defines by what types this entity is blocked.
         * @return The blocking.
         */
        virtual Blocking getBlockedBy() const = 0;

        /**
         * @brief Defines what types this entity blocks.
         * @return The blocking.
         */
        virtual Blocking getBlocking() const = 0;

        /**
         * @brief Get the sorder order of this entity in a block.
         * @return The sort order.
         */
        virtual int getSortOrder() const = 0;

        /**
         * @brief Get the current state id.
         * @return The state id.
         */
        virtual IdPtr getStateId() const = 0;
    };
}

#endif // FRTS_ENTITY_H
