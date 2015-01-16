#ifndef FRTS_VANILLAACTIONPLUGIN_H
#define FRTS_VANILLAACTIONPLUGIN_H

#include "ActionHandler.h"

#include <frts/plugin>


namespace frts
{
    class VanillaActionPlugin : public Plugin
    {
    public:
        VanillaActionPlugin();

        ModulePtr getModule(const IdPtr& id) override;

    private:
        ActionHandlerPtr actionHandler;

    private:
        ActionHandlerPtr getActionHandler();
    };
}

#endif // FRTS_VANILLAACTIONPLUGIN_H
