#ifndef FRTS_MODELFACTORY_H
#define FRTS_MODELFACTORY_H

#include <entity/Component.h>
#include <entity/ComponentBuilder.h>
#include <entity/Entity.h>
#include <region/Block.h>
#include <region/Point.h>
#include <region/Region.h>
#include <regiongenerator/RegionGenerator.h>
#include <regiongenerator/MapParser.h>
#include <pathfinding/DistanceAlgorithm.h>
#include <pathfinding/PathFinder.h>
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
     *        model types like pointer or entities.
     */
    class ModelFactory : public Utility
    {
    public:
        virtual ~ModelFactory() {}

        /**
         * @brief Get default distance algorithm.
         * @return The distance algorithm.
         */
        virtual DistanceAlgorithmPtr getDistanceAlgorithm() const = 0;

        /**
         * @brief Get a map parser for given ID.
         * @throws UnknownMapParserError if there is no map parser registered for the
         *         given ID.
         * @param id The map parser ID.
         * @return The map parser.
         */
        virtual MapParserPtr getMapParser(const IdPtr& id) const = 0;

        /**
         * @brief Get the path finder. The result is undefined before init() is called.
         * @return The path finder.
         */
        virtual PathFinderPtr getPathFinder() const = 0;

        /**
         * @brief Make an empty block. Use for implementations of region managers.
         * @param shared The shared manager.
         * @return The block.
         */
        virtual WriteableBlockPtr makeBlock(const SharedManagerPtr& shared) = 0;

        /**
         * @brief Make a component using the specified builder.
         * @throws UnknownComponentBuilderError if there is not builder registered for the
         *         given ID.
         * @param builderId The builder ID.
         * @return The component.
         */
        virtual ComponentPtr makeComponent(const IdPtr& builderId, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Make an empty entity.
         * @return The entity.
         */
        virtual EntityPtr makeEntity() = 0;

        /**
         * @brief Make an initialized entity from configuration.
         * @throws UnknownEntityError if no configuration for given ID is found.
         * @param id The entity id.
         * @param shared The shared manager.
         * @return The entity.
         */
        virtual EntityPtr makeEntity(const IdPtr& id, const SharedManagerPtr& shared) = 0;

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
        virtual void registerComponentBuilder(const IdPtr& builderId, const ComponentBuilderPtr& builder) = 0;

        /**
         * @brief Register a map parser.
         * @param id The map parser id.
         * @param mapParser The map parser to register.
         */
        virtual void registerMapParser(const IdPtr& id, const MapParserPtr& mapParser) = 0;

        /**
         * @brief Set default distance algorithm. Can be used for example for
         *        resource managers and path finder.
         * @param distanceAlgorithm The distance algorithm.
         */
        virtual void setDistanceAlgorithm(const DistanceAlgorithmPtr& distanceAlgorithm) = 0;

        /**
         * @brief Set the path finder.
         * @param pathFinder The path finder.
         */
        virtual void setPathFinder(const PathFinderPtr& pathFinder) = 0;

        /**
         * @brief Set region. This method has only an effect if it is used
         *        before init().
         * @param region The region.
         */
        virtual void setRegion(const RegionPtr& region) = 0;

        /**
         * @brief Set region generator. Only used for the build in region. This
         *        method has only an effect if it is used before init().
         * @param regionGenerator The region generator.
         */
        virtual void setRegionGenerator(const RegionGeneratorPtr& regionGenerator) = 0;

        /**
         * @brief Set resource entity manager. This method has only an effect
         *        if it is used before init().
         * @param resourceEntityManager The resource manager.
         */
        virtual void setResourceEntityManager(const LockableResourceManagerPtr& resourceEntityManager) = 0;

        /**
         * @brief Set resource manager. This method has only an effect if it is
         *        used before init().
         * @param resourceManager The resource manager.
         */
        virtual void setResourceManager(const LockableResourceManagerPtr& resourceManager) = 0;
    };
}

#endif // FRTS_MODELFACTORY_H
