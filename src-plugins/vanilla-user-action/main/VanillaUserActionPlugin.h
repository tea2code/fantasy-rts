#ifndef FRTS_VANILLAUSERACTIONPLUGIN_H
#define FRTS_VANILLAUSERACTIONPLUGIN_H

#include <frts/plugin>


namespace frts
{
    class VanillaUserActionPlugin : public Plugin
    {
    public:
        VanillaUserActionPlugin();

        ModulePtr getModule(const IdPtr& id) override;
    };
}

#endif // FRTS_VANILLAUSERACTIONPLUGIN_H
