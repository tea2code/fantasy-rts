#ifndef FRTS_VANILLAMODELPLUGIN_H
#define FRTS_VANILLAMODELPLUGIN_H

#include <frts/plugin>

#include <string>


namespace frts
{
    class VanillaModelPlugin : public Plugin
    {
    public:
        const std::string module = "VanillaModel";

    public:
        VanillaModelPlugin();

        ModulePtr getModule(frts::IdPtr id) override;
    };
}

#endif // FRTS_VANILLAMODELPLUGIN_H
