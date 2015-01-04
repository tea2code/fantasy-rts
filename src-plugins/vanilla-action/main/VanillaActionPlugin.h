#ifndef FRTS_VANILLAACTIONPLUGIN_H
#define FRTS_VANILLAACTIONPLUGIN_H

#include <frts/plugin>


namespace frts
{
    class VanillaActionPlugin : public Plugin
    {
    public:
        VanillaActionPlugin();

        ModulePtr getModule(frts::IdPtr id) override;
    };
}

#endif // FRTS_VANILLAACTIONPLUGIN_H
