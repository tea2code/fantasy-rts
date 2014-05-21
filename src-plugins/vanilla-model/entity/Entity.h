#ifndef FRTS_ENTITY_H
#define FRTS_ENTITY_H

#include "Blocking.h"
#include "Component.h"

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
     * @brief A entity consisting of components describing it's abilities.
     */
    class Entity
    {
    public:
        virtual ~Entity() {}

        /**
         * @brief Add component to entity. It will replace another component
         *        with the same type.
         * @param component The component.
         */
        virtual void addComponent(ComponentPtr component) = 0;

        /**
         * @brief Get component with current values.
         * @param type The component type.
         * @return The component or null if not found.
         */
        virtual ComponentPtr getComponent(Component::Type type) const = 0;

        /**
         * @brief Check if entity has the given entity.
         * @param type The component type.
         * @return True if entity has component else false.
         */
        virtual bool hasComponent(Component::Type type) const = 0;

        /**
         * @brief Remove component from entity.
         * @param type The component type.
         */
        virtual void removeComponent(Component::Type type) = 0;
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
