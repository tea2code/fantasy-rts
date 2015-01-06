#ifndef FRTS_VANILLAJOBPLUGIN_H
#define FRTS_VANILLAJOBPLUGIN_H

#include "JobHandler.h"

#include <frts/plugin>


namespace frts
{
    class VanillaJobPlugin : public Plugin
    {
    public:
        VanillaJobPlugin();

        ModulePtr getModule(frts::IdPtr id) override;

    private:
        JobHandlerPtr jobHandler;

    private:
        JobHandlerPtr getJobHandler();
    };
}

#endif // FRTS_VANILLAJOBPLUGIN_H
