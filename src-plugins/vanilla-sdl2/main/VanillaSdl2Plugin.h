#ifndef FRTS_VANILLASDL2PLUGIN_H
#define FRTS_VANILLASDL2PLUGIN_H

#include <input/EventHandler.h>

#include <frts/plugin>

#include <string>


namespace frts
{
    class VanillaSdl2Plugin : public Plugin
    {
    public:
        VanillaSdl2Plugin();

        ModulePtr getModule(frts::IdPtr id) override;

    private:
        EventHandlerPtr eventHandler;

    private:
        EventHandlerPtr getEventHandler();
    };
}

#endif // FRTS_VANILLASDL2PLUGIN_H
