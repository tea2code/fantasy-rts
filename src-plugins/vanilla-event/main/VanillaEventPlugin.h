#ifndef FRTS_VANILLACOMMANDPLUGIN_H
#define FRTS_VANILLACOMMANDPLUGIN_H

#include <frts/plugin>


namespace frts
{
    class VanillaEventPlugin : public Plugin
    {
    public:
        VanillaEventPlugin();

        ModulePtr getModule(frts::IdPtr id) override;
    };
}

#endif // FRTS_VANILLACOMMANDPLUGIN_H
