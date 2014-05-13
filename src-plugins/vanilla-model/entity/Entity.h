#ifndef FRTS_ENTITY_H
#define FRTS_ENTITY_H

#include "Blocking.h"

#include <frts/shared>

#include <functional>
#include <memory>


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
        /**
         * @brief The default sort order.
         */
        const static int defaultSortOrder = 0;

        /**
         * @brief Type of entity.
         */
        enum class Type
        {
            Dynamic,
            Resource,
            Static,
            Tile
        };

    public:
        virtual ~Entity() {}

        /**
         * @brief Defines by what types this entity is blocked.
         * @return The blocking.
         */
        virtual BlockingPtr getBlockedBy() const = 0;

        /**
         * @brief Defines what types this entity blocks.
         * @return The blocking.
         */
        virtual BlockingPtr getBlocking() const = 0;

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

        /**
         * @brief Get the type of entity. This allows fast access to the derived
         *        type without using dynamic_cast (use static_cast instead after
         *        checking the type).
         * @return The type.
         */
        virtual Type getType() const = 0;

        /**
         * @brief Set the sort order. Will only be used the next time this entity
         *        is added to a block.
         * @param sortOrder The sort order.
         */
        virtual void setSortOrder(int sortOrder) = 0;

        /**
         * @brief Set the current state id.
         * @param state The state id.
         */
        virtual void setStateId(IdPtr state) = 0;
    };

    /**
     * @brief Hash function object for entities.
     */
    struct EntityHash
    {
        std::size_t operator() (EntityPtr entity) const
        {
            return ptrHash(entity);
        }

    private:
        std::hash<EntityPtr> ptrHash;
    };

    /**
     * @brief Equal to function object for entities.
     */
    struct EntityEqual
    {
        bool operator() (EntityPtr lhs, EntityPtr rhs) const
        {
            return lhs == rhs;
        }
    };
}

#endif // FRTS_ENTITY_H
