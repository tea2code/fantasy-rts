#ifndef FRTS_COMPONENTBUILDER_H
#define FRTS_COMPONENTBUILDER_H

#include "Component.h"
#include "Entity.h"

#include <frts/configuration>
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
         * @brief Create component.
         * @param entity The entity for which this component is. Some component builders might need
         *               this information.
         * @param shared The shared manager.
         * @return The component.
         */
        virtual ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Create component and initialize with configured data.
         * @param entity The entity for which this component is. Some component builders might need
         *               this information.
         * @param shared The shared manager.
         * @param node The configuration node.
         * @return The component.
         */
        virtual ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node) = 0;
    };
}

#endif // FRTS_COMPONENTBUILDER_H
