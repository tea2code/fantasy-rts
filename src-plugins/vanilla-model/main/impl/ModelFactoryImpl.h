#ifndef FRTS_MODELFACTORYIMPL_H
#define FRTS_MODELFACTORYIMPL_H

#include "ModelDataImpl.h"
#include <main/ModelFactory.h>
#include <region/Region.h>
#include <regiongenerator/RegionGenerator.h>
#include <pathfinding/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>
#include <frts/BaseUtility.h>

#include <unordered_map>
#include <vector>


namespace frts
{
    class ModelFactoryImpl : public BaseUtility<ModelFactory>
    {
    public:
        ModelFactoryImpl();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/ModelFactory";
        }

        void checkRequiredData(SharedManagerPtr shared) override;
        bool createData(SharedManagerPtr shared) override;
        DistanceAlgorithmPtr getDistanceAlgorithm() const override;
        MapParserPtr getMapParser(IdPtr id) const override;
        PathFinderPtr getPathFinder() const override;
        std::vector<std::string> getSupportedConfig() override;
        bool init(SharedManagerPtr shared) override;
        WriteableBlockPtr makeBlock(SharedManagerPtr shared) override;
        ComponentPtr makeComponent(IdPtr builderId, SharedManagerPtr shared) override;
        EntityPtr makeEntity() override;
        EntityPtr makeEntity(IdPtr id, SharedManagerPtr shared) override;
        PointPtr makePoint(Point::value x, Point::value y, Point::value z) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void registerComponentBuilder(IdPtr builderId, ComponentBuilderPtr builder) override;
        void registerMapParser(IdPtr id, MapParserPtr mapParser) override;
        void setDistanceAlgorithm(DistanceAlgorithmPtr distanceAlgorithm) override;
        void setPathFinder(PathFinderPtr pathFinder) override;
        void setRegion(RegionPtr region) override;
        void setRegionGenerator(RegionGeneratorPtr regionGenerator) override;
        void setResourceEntityManager(LockableResourceManagerPtr resourceEntityManager) override;
        void setResourceManager(LockableResourceManagerPtr resourceManager) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        using ComponentBuilderMap = std::unordered_map<IdPtr, ComponentBuilderPtr>;
        using EntityConfigMap = std::unordered_map<IdPtr, std::vector<ConfigNodePtr>>;
        using MapParserMap = std::unordered_map<IdPtr, MapParserPtr>;

    private:
        const std::string entitiesConfigKey = "entities";
        const std::string modelDataKey = "region";
        const std::string unknownComponentBuilderError = R"(%2%: No component builder is registered for ID "%1%".)";
        const std::string unknownMapParserError = R"(%2%: No map parser is registered for ID "%1%".)";

        ComponentBuilderMap componentBuilders;
        DistanceAlgorithmPtr distanceAlgorithm;
        EntityConfigMap entityConfig;
        MapParserMap mapParsers;
        PathFinderPtr pathFinder;
        RegionPtr region;
        RegionGeneratorPtr regionGenerator;
        LockableResourceManagerPtr resourceEntityManager;
        LockableResourceManagerPtr resourceManager;

        bool firstInit = true;

    private:
        ComponentPtr makeComponent(IdPtr builderId, ConfigNodePtr node, SharedManagerPtr shared);
    };

    /**
     * @brief Create new ModelFactory.
     * @return The model factory.
     */
    inline ModelFactoryPtr makeModelFactory()
    {
        return std::make_shared<ModelFactoryImpl>();
    }
}

#endif // FRTS_MODELFACTORYIMPL_H
