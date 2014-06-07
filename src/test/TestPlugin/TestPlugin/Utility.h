#ifndef UTILITY_H
#define UTILITY_H

#include <frts/module>
#include <frts/shared>

class Utility : public frts::Utility
{
public:
    Utility();

    bool createData(frts::SharedManagerPtr shared) override;
    std::string getName() const override;
    std::vector<std::string> getSupportedConfig() override;
    int getVersion() const override;
    bool init(frts::SharedManagerPtr shared) override;
    void parseConfig(const std::string& key, frts::ConfigNodePtr node, frts::SharedManagerPtr shared) override;
    bool preInit(frts::SharedManagerPtr shared) override;
    void validateData(frts::SharedManagerPtr shared) override;
    void validateModules(frts::SharedManagerPtr shared) override;
};

#endif // UTILITY_H
