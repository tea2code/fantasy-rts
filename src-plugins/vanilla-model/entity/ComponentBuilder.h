#ifndef FRTS_COMPONENTBUILDER_H
#define FRTS_COMPONENTBUILDER_H

#include "Component.h"

#include <frts/shared>

#include <memory>


namespace frts
{
    class ComponentBuilder;

    /**
     * @brief Pointer to ComponentBuilder.
     */
    using ComponentBuilderPtr = std::shared_ptr<ComponentBuilder>;

    /**
     * @brief Creates a component.
     */
    class ComponentBuilder
    {
    public:
        virtual ~ComponentBuilder() {}

        /**
         * @brief Create the component.
         * @return The component.
         */
        virtual ComponentPtr build(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_COMPONENTBUILDER_H
