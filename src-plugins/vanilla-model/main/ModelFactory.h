#ifndef FRTS_MODELFACTORY_H
#define FRTS_MODELFACTORY_H

#include <frts/module>

namespace frts
{
    class ModelFactory : public Utility
    {
    public:
        ModelFactory();

        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;
    };
}

#endif // FRTS_MODELFACTORY_H
