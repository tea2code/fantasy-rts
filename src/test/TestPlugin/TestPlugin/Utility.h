#ifndef UTILITY_H
#define UTILITY_H

#include <frts/BaseUtility.h>
#include <frts/module>
#include <frts/shared>

class Utility : public frts::Utility
{
public:
    Utility();

    void checkRequiredData(const frts::SharedManagerPtr& shared) override;
    bool createData(const frts::SharedManagerPtr& shared) override;
    std::string getName() const override;
    std::vector<std::string> getSupportedConfig() override;
    std::string getTypeName() const override;
    int getTypeVersion() const override;
    int getVersion() const override;
    bool init(const frts::SharedManagerPtr& shared) override;
    bool isInitialized() const override;
    bool isPreInitialized() const override;
    void parseConfig(const std::string& key, const frts::ConfigNodePtr& node, const frts::SharedManagerPtr& shared) override;
    bool preInit(const frts::SharedManagerPtr& shared) override;
    void validateData(const frts::SharedManagerPtr& shared) override;
    void validateModules(const frts::SharedManagerPtr& shared) override;
};

#endif // UTILITY_H
