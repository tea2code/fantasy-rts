#ifndef FRTS_VANILLADEMOTICKABLE_H
#define FRTS_VANILLADEMOTICKABLE_H

#include <frts/module>


namespace frts
{
    class VanillaDemoTickable : public Tickable
    {
    public:
        VanillaDemoTickable();

        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared);
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;
    };
}

#endif // FRTS_VANILLADEMOTICKABLE_H
