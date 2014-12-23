#ifndef FRTS_VANILLAEVENTPLUGIN_H
#define FRTS_VANILLAEVENTPLUGIN_H

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

#endif // FRTS_VANILLAEVENTPLUGIN_H
