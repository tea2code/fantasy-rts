#ifndef TICKABLE_H
#define TICKABLE_H

#include <frts/module>
#include <frts/shared>

class Tickable : public frts::Tickable
{
public:
    Tickable();

    void createData(frts::SharedManagerPtr shared) override;
    std::string getName() const override;
    std::vector<std::string> getSupportedConfig() override;
    int getVersion() const override;
    void init(frts::SharedManagerPtr shared) override;
    void parseConfig(frts::ConfigNodePtr node, frts::SharedManagerPtr shared) override;
    void tick(frts::SharedManagerPtr shared);
    void validateData(frts::SharedManagerPtr shared) override;
    void validateModules(frts::SharedManagerPtr shared) override;
};

#endif // TICKABLE_H