#ifndef FRTS_VANILLACOMMANDPLUGIN_H
#define FRTS_VANILLACOMMANDPLUGIN_H

#include <frts/plugin>

#include <string>


namespace frts
{
    class VanillaCommandPlugin : public Plugin
    {
    public:
        VanillaCommandPlugin();

        ModulePtr getModule(frts::IdPtr id) override;
    };
}

#endif // FRTS_VANILLACOMMANDPLUGIN_H
