#ifndef FRTS_VANILLACOMMANDPLUGIN_H
#define FRTS_VANILLACOMMANDPLUGIN_H

#include <frts/plugin>


namespace frts
{
    class VanillaCommandPlugin : public Plugin
    {
    public:
        VanillaCommandPlugin();

        ModulePtr getModule(const IdPtr& id) override;
    };
}

#endif // FRTS_VANILLACOMMANDPLUGIN_H
