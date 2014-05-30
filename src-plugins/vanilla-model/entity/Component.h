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
        virtual ~Component() {}

        /**
         * @brief Get type of component.
         * @return The component type.
         */
        virtual IdPtr getComponentType() const = 0;
    };

    /**
     * @brief Converts a component to the given type if id matches component type.
     * @param type The component type.
     * @param component The component.
     * @return The converted component or null.
     */
    template<typename ComponentClass>
    inline std::shared_ptr<ComponentClass> castComponent(IdPtr type, ComponentPtr component)
    {
        std::shared_ptr<ComponentClass> result = nullptr;
        if (component != nullptr && component->getComponentType() == type)
        {
            result = std::static_pointer_cast<ComponentClass>(component);
        }
        return result;
    }
}

#endif // FRTS_COMPONENT_H
