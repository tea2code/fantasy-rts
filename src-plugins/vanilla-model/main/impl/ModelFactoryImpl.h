#ifndef FRTS_MODELFACTORYIMPL_H
#define FRTS_MODELFACTORYIMPL_H

#include <main/ModelFactory.h>

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
        PointPtr makePoint(Point::value x, Point::value y, Point::value z) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void registerComponentBuilder(IdPtr builderId, ComponentBuilderPtr builder) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        using ComponentBuilderMap = std::unordered_map<IdPtr, ComponentBuilderPtr, IdHash, IdEqual>;

    private:
        ComponentBuilderMap componentBuilders;
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
