#ifndef FRTS_COMPONENT_H
#define FRTS_COMPONENT_H

#include <frts/shared>

#include <memory>


namespace frts
{
    class Component;

    /**
     * @brief Pointer to Component.
     */
    using ComponentPtr = std::shared_ptr<Component>;

    /**
     * @brief Base interface of entity components.
     */
    class Component
    {
    public:
        /**
         * @brief Type of Component.
         */
        using ComponentType = IdPtr;

    public:
        /**
         * @brief Get type of component.
         * @return The component type.
         */
        virtual ComponentType getComponentType() = 0;
    };
}

#endif // FRTS_COMPONENT_H
