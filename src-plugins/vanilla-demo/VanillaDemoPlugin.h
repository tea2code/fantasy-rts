#ifndef FRTS_VANILLADEMOPLUGIN_H
#define FRTS_VANILLADEMOPLUGIN_H

#include <frts/plugin>

#include <string>


namespace frts
{
    class VanillaDemoPlugin : public Plugin
    {
    public:
        VanillaDemoPlugin();

        ModulePtr getModule(frts::IdPtr id) override;
    };
}

#endif // FRTS_VANILLADEMOPLUGIN_H
