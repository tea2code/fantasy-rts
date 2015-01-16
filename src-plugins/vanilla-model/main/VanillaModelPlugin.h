#ifndef FRTS_VANILLAMODELPLUGIN_H
#define FRTS_VANILLAMODELPLUGIN_H

#include <frts/plugin>

#include <string>


namespace frts
{
    class VanillaModelPlugin : public Plugin
    {
    public:
        VanillaModelPlugin();

        ModulePtr getModule(const IdPtr& id) override;
    };
}

#endif // FRTS_VANILLAMODELPLUGIN_H
