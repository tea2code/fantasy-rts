#ifndef FRTS_MODELFACTORYIMPL_H
#define FRTS_MODELFACTORYIMPL_H

#include <main/ModelFactory.h>
#include <main/RegionConfig.h>
#include <region/Region.h>
#include <region/RegionGenerator.h>
#include <resource/DistanceAlgorithm.h>
#include <resource/LockableResourceManager.h>

#include <unordered_map>


namespace frts
{
    class ModelFactoryImpl : public ModelFactory
    {
    public:
        ModelFactoryImpl();

        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        ComponentPtr makeComponent(IdPtr builderId, SharedManagerPtr shared) override;
        EntityPtr makeEntity() override;
        EntityPtr makeEntity(IdPtr id, SharedManagerPtr shared) override;
        PointPtr makePoint(Point::value x, Point::value y, Point::value z) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void registerComponentBuilder(IdPtr builderId, ComponentBuilderPtr builder) override;
        void setDistanceAlgorithm(DistanceAlgorithmPtr distAlgo) override;
        void setHasResourceType(IdPtr hasResourceType) override;
        void setIsResourceType(IdPtr isResourceType) override;
        void setRegion(RegionPtr region) override;
        void setRegionGenerator(RegionGeneratorPtr regionGenerator) override;
        void setResourceEntityManager(LockableResourceManagerPtr resourceEntityManager) override;
        void setResourceManager(LockableResourceManagerPtr resourceManager) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        using ComponentBuilderMap = std::unordered_map<IdPtr, ComponentBuilderPtr, IdHash, IdEqual>;
        using EntityConfigMap = std::unordered_map<IdPtr, ConfigNodePtr, IdHash, IdEqual>;

    private:
        const std::string entitiesConfigKey = "entities";
        const std::string regionConfigKey = "region";
        const std::string unknownComponentBuilderError = R"(No component builder is registered for ID "%1%".)";

        ComponentBuilderMap componentBuilders;
        DistanceAlgorithmPtr distAlgo;
        EntityConfigMap entityConfig;
        IdPtr hasResourceType;
        IdPtr isResourceType;
        RegionPtr region;
        RegionGeneratorPtr regionGenerator;
        LockableResourceManagerPtr resourceEntityManager;
        LockableResourceManagerPtr resourceManager;

    private:
        RegionConfigPtr getRegionConfig(SharedManagerPtr shared) const;
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
