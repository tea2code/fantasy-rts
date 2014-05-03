#ifndef TICKABLE_H
#define TICKABLE_H

#include <frts/module>
#include <frts/shared>

class Tickable : public frts::Tickable
{
public:
    Tickable();

    bool createData(frts::SharedManagerPtr shared) override;
    std::string getName() const override;
    std::vector<std::string> getSupportedConfig() override;
    int getVersion() const override;
    bool init(frts::SharedManagerPtr shared) override;
    void parseConfig(const std::string& key, frts::ConfigNodePtr node, frts::SharedManagerPtr shared) override;
    void tick(frts::SharedManagerPtr shared);
    void validateData(frts::SharedManagerPtr shared) override;
    void validateModules(frts::SharedManagerPtr shared) override;
};

#endif // TICKABLE_H
