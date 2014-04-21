#ifndef MODULE_H
#define MODULE_H

#include <frts/module>
#include <frts/shared>

class Module : public frts::Tickable
{
public:
    Module();

    void createData(frts::SharedManagerPtr shared) override;
    std::string getName() const override;
    std::vector<std::string> getSupportedConfig() override;
    void init(frts::SharedManagerPtr shared) override;
    void parseConfig(frts::ConfigNodePtr node, frts::SharedManagerPtr shared) override;
    void tick(frts::SharedManagerPtr shared);
    void validateData(frts::SharedManagerPtr shared) override;
    void validateModules(frts::SharedManagerPtr shared) override;
};

#endif // MODULE_H
