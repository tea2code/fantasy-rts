#ifndef FRTS_VANILLAJOBPLUGIN_H
#define FRTS_VANILLAJOBPLUGIN_H

#include <frts/plugin>


namespace frts
{
    class VanillaJobPlugin : public Plugin
    {
    public:
        VanillaJobPlugin();

        ModulePtr getModule(frts::IdPtr id) override;
    };
}

#endif // FRTS_VANILLAJOBPLUGIN_H
