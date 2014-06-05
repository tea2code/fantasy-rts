#ifndef FRTS_MODELFACTORY_H
#define FRTS_MODELFACTORY_H

#include <entity/Component.h>
#include <entity/ComponentBuilder.h>
#include <entity/Entity.h>
#include <region/Point.h>

#include <frts/module>
#include <frts/shared>

#include <memory>


namespace frts
{
    class ModelFactory;

    /**
     * @brief Pointer to ModelFactory.
     */
    using ModelFactoryPtr = std::shared_ptr<ModelFactory>;

    /**
     * @brief Model factory is a utility which allows creation of several
     * model types like pointer or entities.
     */
    class ModelFactory : public Utility
    {
    public:
        virtual ~ModelFactory() {}

        /**
         * @brief Make a component using the specified builder.
         * @throws UnknownBuilderError if there is not builder registered for the
         *         given ID.
         * @param builderId The builder ID.
         * @return The component.
         */
        virtual ComponentPtr makeComponent(IdPtr builderId, SharedManagerPtr shared) = 0;

        /**
         * @brief Make an empty enttiy.
         * @return The entity;
         */
        virtual EntityPtr makeEntity() = 0;

       /**
        * @brief Create a new point.
        * @param x The x coordinate.
        * @param y The y coordinate.
        * @param z The z coordinate.
        * @return The point pointer.
        */
        virtual PointPtr makePoint(Point::value x, Point::value y, Point::value z) = 0;

        /**
         * @brief Register a component builder.
         * @param builderId The builder ID. This may be the component type id
         *                  and in most cases that's the most reasonable choice.
         *                  But there may be scenarios where it is better to
         *                  use another ID. For example to register the same
         *                  builder with different initialization several times.
         * @param builder The builder to register.
         */
        virtual void registerComponentBuilder(IdPtr builderId, ComponentBuilderPtr builder) = 0;
    };
}

#endif // FRTS_MODELFACTORY_H
