#ifndef FRTS_MODELFACTORY_H
#define FRTS_MODELFACTORY_H

#include <entity/Component.h>
#include <entity/ComponentBuilder.h>
#include <entity/Entity.h>
#include <region/Point.h>
#include <region/Region.h>
#include <region/RegionGenerator.h>
#include <resource/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>

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
         * @brief Make an empty entity.
         * @return The entity;
         */
        virtual EntityPtr makeEntity() = 0;

        /**
         * @brief Make an initialized entity from configuration.
         * @throws UnknownEntityError if no configuration for given ID is found.
         * @param id The entity id.
         * @param shared The shared manager.
         * @return The entity;
         */
        virtual EntityPtr makeEntity(IdPtr id, SharedManagerPtr shared) = 0;

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

        /**
         * @brief Set distance algorithm for resource managers. Only used for the
         *        build in resource managers. This method has only an effect
         *        if it is used before init().
         * @param distAlgo The distance algorithm.
         */
        virtual void setDistanceAlgorithm(DistanceAlgorithmPtr distAlgo) = 0;

        /**
         * @brief Set has resource type. Only used for the build in resource
         *        managers. This method has only an effect if it is used before
         *        init().
         * @param hasResourceType The resource type.
         */
        virtual void setHasResourceType(IdPtr hasResourceType) = 0;

        /**
         * @brief Set is resource type. Only used for the build in resource
         *        managers. This method has only an effect if it is used before
         *        init().
         * @param isResourceType The resource type.
         */
        virtual void setIsResourceType(IdPtr isResourceType) = 0;

        /**
         * @brief Set region. This method has only an effect if it is used
         *        before init().
         * @param region The region.
         */
        virtual void setRegion(RegionPtr region) = 0;

        /**
         * @brief Set region generator. Only used for the build in region. This
         *        method has only an effect if it is used before init().
         * @param regionGenerator The region generator.
         */
        virtual void setRegionGenerator(RegionGeneratorPtr regionGenerator) = 0;

        /**
         * @brief Set resource entity manager.  This method has only an effect
         *        if it is used before init().
         * @param resourceEntityManager The resource manager.
         */
        virtual void setResourceEntityManager(LockableResourceManagerPtr resourceEntityManager) = 0;

        /**
         * @brief Set resource manager. This method has only an effect if it is
         *        used before init().
         * @param resourceManager The resource manager.
         */
        virtual void setResourceManager(LockableResourceManagerPtr resourceManager) = 0;
    };
}

#endif // FRTS_MODELFACTORY_H
